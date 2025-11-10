#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/compiler.h"

// Utility functions
char* string_copy(const char* str, int length) {
    char* copy = malloc(length + 1);
    memcpy(copy, str, length);
    copy[length] = '\0';
    return copy;
}

void error(int line, const char* message) {
    fprintf(stderr, "[Line %d] Error: %s\n", line, message);
}

// AST creation
ASTNode* ast_create_node(ASTNodeType type, int line) {
    ASTNode* node = calloc(1, sizeof(ASTNode));
    node->type = type;
    node->line = line;
    return node;
}

void ast_free(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_PROGRAM:
            for (int i = 0; i < node->program.enum_count; i++) {
                ast_free(node->program.enums[i]);
            }
            free(node->program.enums);
            for (int i = 0; i < node->program.function_count; i++) {
                ast_free(node->program.functions[i]);
            }
            free(node->program.functions);
            break;
        case AST_FUNCTION:
            for (int i = 0; i < node->function.param_count; i++) {
                free(node->function.param_names[i]);
                free(node->function.param_types[i]);
            }
            free(node->function.param_names);
            free(node->function.param_types);
            free(node->function.name);
            free(node->function.return_type);
            ast_free(node->function.body);
            break;
        case AST_BLOCK:
            for (int i = 0; i < node->block.statement_count; i++) {
                ast_free(node->block.statements[i]);
            }
            free(node->block.statements);
            break;
        case AST_BINARY_OP:
            ast_free(node->binary.left);
            ast_free(node->binary.right);
            break;
        case AST_UNARY_OP:
            ast_free(node->unary.operand);
            break;
        case AST_POSTFIX_OP:
            ast_free(node->postfix.operand);
            break;
        case AST_CALL:
            for (int i = 0; i < node->call.arg_count; i++) {
                ast_free(node->call.args[i]);
            }
            free(node->call.args);
            free(node->call.name);
            break;
        case AST_DECLARATION:
            free(node->declaration.name);
            free(node->declaration.type);
            ast_free(node->declaration.initializer);
            break;
        case AST_ASSIGNMENT:
            free(node->assignment.name);
            ast_free(node->assignment.value);
            break;
        case AST_IF_STMT:
            ast_free(node->if_stmt.condition);
            ast_free(node->if_stmt.then_branch);
            ast_free(node->if_stmt.else_branch);
            break;
        case AST_WHILE_STMT:
            ast_free(node->while_stmt.condition);
            ast_free(node->while_stmt.body);
            break;
        case AST_DO_WHILE_STMT:
            ast_free(node->do_while_stmt.body);
            ast_free(node->do_while_stmt.condition);
            break;
        case AST_FOR_STMT:
            ast_free(node->for_stmt.init);
            ast_free(node->for_stmt.condition);
            ast_free(node->for_stmt.increment);
            ast_free(node->for_stmt.body);
            break;
        case AST_SWITCH_STMT:
            ast_free(node->switch_stmt.expression);
            ast_free(node->switch_stmt.body);
            break;
        case AST_CASE_STMT:
            ast_free(node->case_stmt.body);
            break;
        case AST_DEFAULT_STMT:
            ast_free(node->default_stmt.body);
            break;
        case AST_GOTO_STMT:
            free(node->goto_stmt.label);
            break;
        case AST_LABEL_STMT:
            free(node->label_stmt.name);
            ast_free(node->label_stmt.statement);
            break;
        case AST_TERNARY_OP:
            ast_free(node->ternary_op.condition);
            ast_free(node->ternary_op.true_expr);
            ast_free(node->ternary_op.false_expr);
            break;
        case AST_SIZEOF:
            free(node->sizeof_expr.type_name);
            ast_free(node->sizeof_expr.expr);
            break;
        case AST_ENUM_DECL:
            free(node->enum_decl.name);
            for (int i = 0; i < node->enum_decl.value_count; i++) {
                free(node->enum_decl.value_names[i]);
            }
            free(node->enum_decl.value_names);
            free(node->enum_decl.values);
            break;
        case AST_RETURN_STMT:
            ast_free(node->return_stmt.value);
            break;
        case AST_EXPRESSION_STMT:
            ast_free(node->expr_stmt.expression);
            break;
        case AST_LITERAL_STRING:
            free(node->string.value);
            break;
        case AST_IDENTIFIER:
            free(node->identifier.name);
            break;
        default:
            break;
    }
    
    free(node);
}

// Parser helper functions
static void advance(Parser* p) {
    p->previous = p->current;
    
    for (;;) {
        p->current = lexer_scan_token(p->lexer);
        if (p->current.type != TOKEN_ERROR) break;
        
        parser_error_at(p, &p->current, p->current.start);
    }
}

static bool check(Parser* p, TokenType type) {
    return p->current.type == type;
}

// Check if current token is identifier and next is colon (for labels)
static bool check_label(Parser* p) {
    if (p->current.type != TOKEN_IDENTIFIER) return false;
    
    // We need to peek ahead - save current state
    Lexer saved_lexer = *p->lexer;
    Token next = lexer_scan_token(p->lexer);
    *p->lexer = saved_lexer;  // Restore lexer state
    
    return next.type == TOKEN_COLON;
}

static bool match(Parser* p, TokenType type) {
    if (!check(p, type)) return false;
    advance(p);
    return true;
}

static void consume(Parser* p, TokenType type, const char* message) {
    if (p->current.type == type) {
        advance(p);
        return;
    }
    parser_error_at(p, &p->current, message);
}

void parser_error_at(Parser* p, Token* token, const char* message) {
    if (p->panic_mode) return;
    p->panic_mode = true;
    p->had_error = true;
    
    fprintf(stderr, "[Line %d] Error", token->line);
    
    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // Nothing
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }
    
    fprintf(stderr, ": %s\n", message);
}

// Forward declarations
static ASTNode* expression(Parser* p);
static ASTNode* statement(Parser* p);
static ASTNode* postfix(Parser* p);
static ASTNode* enum_decl(Parser* p);

// Expression parsing with precedence
static ASTNode* primary(Parser* p) {
    if (match(p, TOKEN_TRUE)) {
        ASTNode* node = ast_create_node(AST_LITERAL_BOOL, p->previous.line);
        node->boolean.value = true;
        return node;
    }
    
    if (match(p, TOKEN_FALSE)) {
        ASTNode* node = ast_create_node(AST_LITERAL_BOOL, p->previous.line);
        node->boolean.value = false;
        return node;
    }
    
    if (match(p, TOKEN_INTEGER)) {
        ASTNode* node = ast_create_node(AST_LITERAL_INT, p->previous.line);
        node->integer.value = strtoll(p->previous.start, NULL, 10);
        return node;
    }
    
    if (match(p, TOKEN_STRING)) {
        ASTNode* node = ast_create_node(AST_LITERAL_STRING, p->previous.line);
        // Remove quotes
        node->string.value = string_copy(p->previous.start + 1, p->previous.length - 2);
        return node;
    }
    
    if (match(p, TOKEN_IDENTIFIER)) {
        char* name = string_copy(p->previous.start, p->previous.length);
        
        if (match(p, TOKEN_LEFT_PAREN)) {
            // Function call
            ASTNode* node = ast_create_node(AST_CALL, p->previous.line);
            node->call.name = name;
            node->call.args = NULL;
            node->call.arg_count = 0;
            
            if (!check(p, TOKEN_RIGHT_PAREN)) {
                int capacity = 4;
                node->call.args = malloc(sizeof(ASTNode*) * capacity);
                
                do {
                    if (node->call.arg_count >= capacity) {
                        capacity *= 2;
                        node->call.args = realloc(node->call.args, sizeof(ASTNode*) * capacity);
                    }
                    node->call.args[node->call.arg_count++] = expression(p);
                } while (match(p, TOKEN_COMMA));
            }
            
            consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after arguments");
            return node;
        } else {
            // Variable reference
            ASTNode* node = ast_create_node(AST_IDENTIFIER, p->previous.line);
            node->identifier.name = name;
            return node;
        }
    }
    
    if (match(p, TOKEN_LEFT_PAREN)) {
        ASTNode* expr = expression(p);
        consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after expression");
        return expr;
    }
    
    parser_error_at(p, &p->current, "Expected expression");
    return NULL;
}

static ASTNode* unary(Parser* p) {
    if (match(p, TOKEN_SIZEOF)) {
        ASTNode* node = ast_create_node(AST_SIZEOF, p->previous.line);
        
        // sizeof can take (type) or expression
        if (match(p, TOKEN_LEFT_PAREN)) {
            // Check if it's a type name
            if (match(p, TOKEN_INT) || match(p, TOKEN_BOOL) || match(p, TOKEN_CHAR) ||
                match(p, TOKEN_SHORT) || match(p, TOKEN_LONG) || match(p, TOKEN_FLOAT) ||
                match(p, TOKEN_DOUBLE) || match(p, TOKEN_VOID)) {
                
                // Store the type as a string
                node->sizeof_expr.type_name = string_copy(p->previous.start, p->previous.length);
                node->sizeof_expr.expr = NULL;
                consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after type name");
            } else {
                // It's an expression in parentheses
                node->sizeof_expr.type_name = NULL;
                node->sizeof_expr.expr = expression(p);
                consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after expression");
            }
        } else {
            // sizeof without parentheses - parse unary expression
            node->sizeof_expr.type_name = NULL;
            node->sizeof_expr.expr = unary(p);
        }
        
        return node;
    }
    
    if (match(p, TOKEN_PLUS_PLUS) || match(p, TOKEN_MINUS_MINUS)) {
        Token op = p->previous;
        ASTNode* node = ast_create_node(AST_UNARY_OP, op.line);
        node->unary.op = op.type;
        node->unary.operand = unary(p);
        return node;
    }
    
    if (match(p, TOKEN_AMPERSAND) || match(p, TOKEN_STAR) || 
        match(p, TOKEN_BANG) || match(p, TOKEN_MINUS) || match(p, TOKEN_TILDE)) {
        Token op = p->previous;
        ASTNode* node = ast_create_node(AST_UNARY_OP, op.line);
        node->unary.op = op.type;
        node->unary.operand = unary(p);
        return node;
    }
    
    return postfix(p);
}

static ASTNode* postfix(Parser* p) {
    ASTNode* node = primary(p);
    
    while (match(p, TOKEN_PLUS_PLUS) || match(p, TOKEN_MINUS_MINUS)) {
        Token op = p->previous;
        ASTNode* postfix_node = ast_create_node(AST_POSTFIX_OP, op.line);
        postfix_node->postfix.operand = node;
        postfix_node->postfix.op = op.type;
        node = postfix_node;
    }
    
    return node;
}

static ASTNode* binary_op(Parser* p, ASTNode* (*higher_prec)(Parser*), 
                          TokenType* ops, int op_count) {
    ASTNode* left = higher_prec(p);
    
    while (true) {
        bool matched = false;
        for (int i = 0; i < op_count; i++) {
            if (match(p, ops[i])) {
                Token op = p->previous;
                ASTNode* right = higher_prec(p);
                ASTNode* node = ast_create_node(AST_BINARY_OP, op.line);
                node->binary.left = left;
                node->binary.right = right;
                node->binary.op = op.type;
                left = node;
                matched = true;
                break;
            }
        }
        if (!matched) break;
    }
    
    return left;
}

static ASTNode* multiplication(Parser* p) {
    TokenType ops[] = {TOKEN_STAR, TOKEN_SLASH, TOKEN_PERCENT};
    return binary_op(p, unary, ops, 3);
}

static ASTNode* addition(Parser* p) {
    TokenType ops[] = {TOKEN_PLUS, TOKEN_MINUS};
    return binary_op(p, multiplication, ops, 2);
}

static ASTNode* shift(Parser* p) {
    TokenType ops[] = {TOKEN_LEFT_SHIFT, TOKEN_RIGHT_SHIFT};
    return binary_op(p, addition, ops, 2);
}

static ASTNode* comparison(Parser* p) {
    TokenType ops[] = {TOKEN_LESS, TOKEN_LESS_EQUAL, TOKEN_GREATER, TOKEN_GREATER_EQUAL};
    return binary_op(p, shift, ops, 4);
}

static ASTNode* equality(Parser* p) {
    TokenType ops[] = {TOKEN_EQUAL_EQUAL, TOKEN_BANG_EQUAL};
    return binary_op(p, comparison, ops, 2);
}

static ASTNode* bitwise_and(Parser* p) {
    TokenType ops[] = {TOKEN_AMPERSAND};
    return binary_op(p, equality, ops, 1);
}

static ASTNode* bitwise_xor(Parser* p) {
    TokenType ops[] = {TOKEN_CARET};
    return binary_op(p, bitwise_and, ops, 1);
}

static ASTNode* bitwise_or(Parser* p) {
    TokenType ops[] = {TOKEN_PIPE};
    return binary_op(p, bitwise_xor, ops, 1);
}

static ASTNode* logical_and(Parser* p) {
    TokenType ops[] = {TOKEN_AMPERSAND_AMPERSAND};
    return binary_op(p, bitwise_or, ops, 1);
}

static ASTNode* logical_or(Parser* p) {
    TokenType ops[] = {TOKEN_PIPE_PIPE};
    return binary_op(p, logical_and, ops, 1);
}

static ASTNode* ternary(Parser* p) {
    ASTNode* node = logical_or(p);
    
    if (match(p, TOKEN_QUESTION)) {
        ASTNode* ternary_node = ast_create_node(AST_TERNARY_OP, p->previous.line);
        ternary_node->ternary_op.condition = node;
        ternary_node->ternary_op.true_expr = expression(p);
        consume(p, TOKEN_COLON, "Expected ':' after true expression in ternary operator");
        ternary_node->ternary_op.false_expr = expression(p);
        return ternary_node;
    }
    
    return node;
}

static ASTNode* expression(Parser* p) {
    return ternary(p);
}

// Statement parsing
static ASTNode* declaration_stmt(Parser* p) {
    bool is_const = p->previous.type == TOKEN_CONST;
    consume(p, TOKEN_IDENTIFIER, "Expected variable name");
    
    ASTNode* node = ast_create_node(AST_DECLARATION, p->previous.line);
    node->declaration.name = string_copy(p->previous.start, p->previous.length);
    node->declaration.is_const = is_const;
    node->declaration.type = NULL;
    
    if (match(p, TOKEN_COLON)) {
        // Allow type keywords or identifiers as types
        if (!match(p, TOKEN_INT) && !match(p, TOKEN_BOOL) && 
            !match(p, TOKEN_STRING_TYPE) && !match(p, TOKEN_VOID) &&
            !match(p, TOKEN_IDENTIFIER)) {
            parser_error_at(p, &p->current, "Expected type name");
        }
        node->declaration.type = string_copy(p->previous.start, p->previous.length);
    }
    
    consume(p, TOKEN_EQUAL, "Expected '=' in declaration");
    node->declaration.initializer = expression(p);
    consume(p, TOKEN_SEMICOLON, "Expected ';' after declaration");
    
    return node;
}

static ASTNode* if_stmt(Parser* p) {
    ASTNode* node = ast_create_node(AST_IF_STMT, p->previous.line);
    
    consume(p, TOKEN_LEFT_PAREN, "Expected '(' after 'if'");
    node->if_stmt.condition = expression(p);
    consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after condition");
    
    node->if_stmt.then_branch = statement(p);
    node->if_stmt.else_branch = NULL;
    
    if (match(p, TOKEN_ELSE)) {
        node->if_stmt.else_branch = statement(p);
    }
    
    return node;
}

static ASTNode* while_stmt(Parser* p) {
    ASTNode* node = ast_create_node(AST_WHILE_STMT, p->previous.line);
    
    consume(p, TOKEN_LEFT_PAREN, "Expected '(' after 'while'");
    node->while_stmt.condition = expression(p);
    consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after condition");
    
    node->while_stmt.body = statement(p);
    
    return node;
}

static ASTNode* do_while_stmt(Parser* p) {
    ASTNode* node = ast_create_node(AST_DO_WHILE_STMT, p->previous.line);
    
    node->do_while_stmt.body = statement(p);
    
    consume(p, TOKEN_WHILE, "Expected 'while' after do body");
    consume(p, TOKEN_LEFT_PAREN, "Expected '(' after 'while'");
    node->do_while_stmt.condition = expression(p);
    consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after condition");
    consume(p, TOKEN_SEMICOLON, "Expected ';' after do-while");
    
    return node;
}

static ASTNode* for_stmt(Parser* p) {
    ASTNode* node = ast_create_node(AST_FOR_STMT, p->previous.line);
    
    consume(p, TOKEN_LEFT_PAREN, "Expected '(' after 'for'");
    
    // Initializer
    if (match(p, TOKEN_LET) || match(p, TOKEN_CONST)) {
        node->for_stmt.init = declaration_stmt(p);
    } else {
        consume(p, TOKEN_SEMICOLON, "Expected ';'");
        node->for_stmt.init = NULL;
    }
    
    // Condition
    if (!check(p, TOKEN_SEMICOLON)) {
        node->for_stmt.condition = expression(p);
    }
    consume(p, TOKEN_SEMICOLON, "Expected ';' after condition");
    
    // Increment
    if (!check(p, TOKEN_RIGHT_PAREN)) {
        // Parse as assignment
        consume(p, TOKEN_IDENTIFIER, "Expected identifier");
        char* name = string_copy(p->previous.start, p->previous.length);
        consume(p, TOKEN_EQUAL, "Expected '='");
        ASTNode* inc = ast_create_node(AST_ASSIGNMENT, p->previous.line);
        inc->assignment.name = name;
        inc->assignment.value = expression(p);
        node->for_stmt.increment = inc;
    }
    
    consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after clauses");
    
    node->for_stmt.body = statement(p);
    
    return node;
}

static ASTNode* switch_stmt(Parser* p) {
    ASTNode* node = ast_create_node(AST_SWITCH_STMT, p->previous.line);
    
    consume(p, TOKEN_LEFT_PAREN, "Expected '(' after 'switch'");
    node->switch_stmt.expression = expression(p);
    consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after switch expression");
    
    consume(p, TOKEN_LEFT_BRACE, "Expected '{' after switch header");
    
    // Parse the body as a block containing case/default statements
    ASTNode* block = ast_create_node(AST_BLOCK, p->current.line);
    block->block.statements = NULL;
    block->block.statement_count = 0;
    block->block.capacity = 0;
    
    while (!check(p, TOKEN_RIGHT_BRACE) && p->current.type != TOKEN_EOF) {
        ASTNode* stmt = NULL;
        
        if (match(p, TOKEN_CASE)) {
            stmt = ast_create_node(AST_CASE_STMT, p->previous.line);
            
            // Parse case value (must be integer literal)
            if (!match(p, TOKEN_INTEGER)) {
                parser_error_at(p, &p->current, "Expected integer literal after 'case'");
            }
            stmt->case_stmt.value = strtoll(p->previous.start, NULL, 10);
            
            consume(p, TOKEN_COLON, "Expected ':' after case value");
            
            // Parse statements until next case/default/}
            ASTNode* case_block = ast_create_node(AST_BLOCK, p->current.line);
            case_block->block.statements = NULL;
            case_block->block.statement_count = 0;
            case_block->block.capacity = 0;
            
            while (!check(p, TOKEN_CASE) && !check(p, TOKEN_DEFAULT) && 
                   !check(p, TOKEN_RIGHT_BRACE) && p->current.type != TOKEN_EOF) {
                ASTNode* s = statement(p);
                if (case_block->block.statement_count >= case_block->block.capacity) {
                    int old_cap = case_block->block.capacity;
                    case_block->block.capacity = old_cap < 8 ? 8 : old_cap * 2;
                    case_block->block.statements = realloc(case_block->block.statements,
                        sizeof(ASTNode*) * case_block->block.capacity);
                }
                case_block->block.statements[case_block->block.statement_count++] = s;
            }
            
            stmt->case_stmt.body = case_block;
        } else if (match(p, TOKEN_DEFAULT)) {
            stmt = ast_create_node(AST_DEFAULT_STMT, p->previous.line);
            consume(p, TOKEN_COLON, "Expected ':' after 'default'");
            
            // Parse statements until next case/}
            ASTNode* default_block = ast_create_node(AST_BLOCK, p->current.line);
            default_block->block.statements = NULL;
            default_block->block.statement_count = 0;
            default_block->block.capacity = 0;
            
            while (!check(p, TOKEN_CASE) && !check(p, TOKEN_DEFAULT) && 
                   !check(p, TOKEN_RIGHT_BRACE) && p->current.type != TOKEN_EOF) {
                ASTNode* s = statement(p);
                if (default_block->block.statement_count >= default_block->block.capacity) {
                    int old_cap = default_block->block.capacity;
                    default_block->block.capacity = old_cap < 8 ? 8 : old_cap * 2;
                    default_block->block.statements = realloc(default_block->block.statements,
                        sizeof(ASTNode*) * default_block->block.capacity);
                }
                default_block->block.statements[default_block->block.statement_count++] = s;
            }
            
            stmt->default_stmt.body = default_block;
        } else {
            parser_error_at(p, &p->current, "Expected 'case' or 'default' in switch body");
        }
        
        if (stmt) {
            if (block->block.statement_count >= block->block.capacity) {
                int old_cap = block->block.capacity;
                block->block.capacity = old_cap < 8 ? 8 : old_cap * 2;
                block->block.statements = realloc(block->block.statements,
                    sizeof(ASTNode*) * block->block.capacity);
            }
            block->block.statements[block->block.statement_count++] = stmt;
        }
    }
    
    consume(p, TOKEN_RIGHT_BRACE, "Expected '}' after switch body");
    
    node->switch_stmt.body = block;
    return node;
}

static ASTNode* return_stmt(Parser* p) {
    ASTNode* node = ast_create_node(AST_RETURN_STMT, p->previous.line);
    
    if (!check(p, TOKEN_SEMICOLON)) {
        node->return_stmt.value = expression(p);
    } else {
        node->return_stmt.value = NULL;
    }
    
    consume(p, TOKEN_SEMICOLON, "Expected ';' after return");
    return node;
}

static ASTNode* block(Parser* p) {
    ASTNode* node = ast_create_node(AST_BLOCK, p->current.line);
    node->block.statements = malloc(sizeof(ASTNode*) * 8);  // Smaller initial size
    node->block.capacity = 8;
    node->block.statement_count = 0;
    
    while (!check(p, TOKEN_RIGHT_BRACE) && !check(p, TOKEN_EOF)) {
        if (node->block.statement_count >= node->block.capacity) {
            node->block.capacity *= 2;
            node->block.statements = realloc(node->block.statements, 
                                           sizeof(ASTNode*) * node->block.capacity);
        }
        node->block.statements[node->block.statement_count++] = statement(p);
    }
    
    consume(p, TOKEN_RIGHT_BRACE, "Expected '}' after block");
    return node;
}

static ASTNode* enum_decl(Parser* p) {
    ASTNode* node = ast_create_node(AST_ENUM_DECL, p->previous.line);
    
    // Optional enum name
    if (match(p, TOKEN_IDENTIFIER)) {
        node->enum_decl.name = string_copy(p->previous.start, p->previous.length);
    } else {
        node->enum_decl.name = NULL;
    }
    
    consume(p, TOKEN_LEFT_BRACE, "Expected '{' after enum");
    
    // Parse enum values
    int capacity = 8;
    node->enum_decl.value_names = malloc(sizeof(char*) * capacity);
    node->enum_decl.values = malloc(sizeof(int64_t) * capacity);
    node->enum_decl.value_count = 0;
    
    int64_t next_value = 0;
    
    while (!check(p, TOKEN_RIGHT_BRACE) && !check(p, TOKEN_EOF)) {
        if (node->enum_decl.value_count >= capacity) {
            capacity *= 2;
            node->enum_decl.value_names = realloc(node->enum_decl.value_names, sizeof(char*) * capacity);
            node->enum_decl.values = realloc(node->enum_decl.values, sizeof(int64_t) * capacity);
        }
        
        consume(p, TOKEN_IDENTIFIER, "Expected enum value name");
        node->enum_decl.value_names[node->enum_decl.value_count] = 
            string_copy(p->previous.start, p->previous.length);
        
        // Check for explicit value
        if (match(p, TOKEN_EQUAL)) {
            consume(p, TOKEN_INTEGER, "Expected integer value");
            next_value = strtoll(p->previous.start, NULL, 10);
        }
        
        node->enum_decl.values[node->enum_decl.value_count] = next_value;
        node->enum_decl.value_count++;
        next_value++;
        
        if (!match(p, TOKEN_COMMA)) {
            break;
        }
    }
    
    consume(p, TOKEN_RIGHT_BRACE, "Expected '}' after enum values");
    
    return node;
}

static ASTNode* statement(Parser* p) {
    if (match(p, TOKEN_ENUM)) return enum_decl(p);
    if (match(p, TOKEN_IF)) return if_stmt(p);
    if (match(p, TOKEN_WHILE)) return while_stmt(p);
    if (match(p, TOKEN_DO)) return do_while_stmt(p);
    if (match(p, TOKEN_FOR)) return for_stmt(p);
    if (match(p, TOKEN_SWITCH)) return switch_stmt(p);
    if (match(p, TOKEN_RETURN)) return return_stmt(p);
    if (match(p, TOKEN_LEFT_BRACE)) return block(p);
    if (match(p, TOKEN_LET) || match(p, TOKEN_CONST)) return declaration_stmt(p);
    
    if (match(p, TOKEN_BREAK)) {
        ASTNode* node = ast_create_node(AST_BREAK, p->previous.line);
        consume(p, TOKEN_SEMICOLON, "Expected ';' after 'break'");
        return node;
    }
    
    if (match(p, TOKEN_CONTINUE)) {
        ASTNode* node = ast_create_node(AST_CONTINUE, p->previous.line);
        consume(p, TOKEN_SEMICOLON, "Expected ';' after 'continue'");
        return node;
    }
    
    if (match(p, TOKEN_GOTO)) {
        ASTNode* node = ast_create_node(AST_GOTO_STMT, p->previous.line);
        consume(p, TOKEN_IDENTIFIER, "Expected label name after 'goto'");
        node->goto_stmt.label = string_copy(p->previous.start, p->previous.length);
        consume(p, TOKEN_SEMICOLON, "Expected ';' after goto statement");
        return node;
    }
    
    // Check for label (identifier followed by colon)
    if (check_label(p)) {
        advance(p);  // consume identifier
        Token label_token = p->previous;
        consume(p, TOKEN_COLON, "Expected ':'");  // consume colon
        
        ASTNode* node = ast_create_node(AST_LABEL_STMT, label_token.line);
        node->label_stmt.name = string_copy(label_token.start, label_token.length);
        node->label_stmt.statement = statement(p);  // Parse the statement after the label
        return node;
    }
    
    // Expression statement (which includes assignments via special handling)
    ASTNode* expr = expression(p);
    
    // Special case: if expression is just an identifier followed by assignment operator
    if (expr->type == AST_IDENTIFIER) {
        TokenType compound_op = TOKEN_EOF;
        
        if (check(p, TOKEN_EQUAL)) {
            // Regular assignment: x = value
            advance(p);  // consume =
            char* name = expr->identifier.name;
            expr->identifier.name = NULL;  // Prevent double-free
            int line = expr->line;
            ast_free(expr);
            
            ASTNode* node = ast_create_node(AST_ASSIGNMENT, line);
            node->assignment.name = name;
            node->assignment.value = expression(p);
            consume(p, TOKEN_SEMICOLON, "Expected ';' after assignment");
            return node;
        } else if (match(p, TOKEN_PLUS_EQUAL) || match(p, TOKEN_MINUS_EQUAL) ||
                   match(p, TOKEN_STAR_EQUAL) || match(p, TOKEN_SLASH_EQUAL) ||
                   match(p, TOKEN_PERCENT_EQUAL) || match(p, TOKEN_AMPERSAND_EQUAL) ||
                   match(p, TOKEN_PIPE_EQUAL) || match(p, TOKEN_CARET_EQUAL) ||
                   match(p, TOKEN_LEFT_SHIFT_EQUAL) || match(p, TOKEN_RIGHT_SHIFT_EQUAL)) {
            // Compound assignment: x += value, etc.
            compound_op = p->previous.type;
            char* name = expr->identifier.name;
            int line = expr->line;
            
            // Convert compound assignment to regular assignment
            // x += 5 becomes x = x + 5
            ASTNode* right_expr = expression(p);
            
            // Create a binary operation: x op value
            ASTNode* var_node = ast_create_node(AST_IDENTIFIER, line);
            var_node->identifier.name = strdup(name);  // Duplicate for binary op
            
            ASTNode* binary = ast_create_node(AST_BINARY_OP, line);
            binary->binary.left = var_node;
            binary->binary.right = right_expr;
            
            // Map compound operator to binary operator
            switch (compound_op) {
                case TOKEN_PLUS_EQUAL: binary->binary.op = TOKEN_PLUS; break;
                case TOKEN_MINUS_EQUAL: binary->binary.op = TOKEN_MINUS; break;
                case TOKEN_STAR_EQUAL: binary->binary.op = TOKEN_STAR; break;
                case TOKEN_SLASH_EQUAL: binary->binary.op = TOKEN_SLASH; break;
                case TOKEN_PERCENT_EQUAL: binary->binary.op = TOKEN_PERCENT; break;
                case TOKEN_AMPERSAND_EQUAL: binary->binary.op = TOKEN_AMPERSAND; break;
                case TOKEN_PIPE_EQUAL: binary->binary.op = TOKEN_PIPE; break;
                case TOKEN_CARET_EQUAL: binary->binary.op = TOKEN_CARET; break;
                case TOKEN_LEFT_SHIFT_EQUAL: binary->binary.op = TOKEN_LEFT_SHIFT; break;
                case TOKEN_RIGHT_SHIFT_EQUAL: binary->binary.op = TOKEN_RIGHT_SHIFT; break;
                default: binary->binary.op = TOKEN_PLUS; break;
            }
            
            expr->identifier.name = NULL;  // Prevent double-free
            ast_free(expr);
            
            ASTNode* node = ast_create_node(AST_ASSIGNMENT, line);
            node->assignment.name = name;
            node->assignment.value = binary;
            consume(p, TOKEN_SEMICOLON, "Expected ';' after assignment");
            return node;
        }
    }
    
    // Regular expression statement
    ASTNode* node = ast_create_node(AST_EXPRESSION_STMT, expr->line);
    node->expr_stmt.expression = expr;
    consume(p, TOKEN_SEMICOLON, "Expected ';' after expression");
    return node;
}

static ASTNode* function_decl(Parser* p) {
    consume(p, TOKEN_IDENTIFIER, "Expected function name");
    
    ASTNode* node = ast_create_node(AST_FUNCTION, p->previous.line);
    node->function.name = string_copy(p->previous.start, p->previous.length);
    
    // Parameters
    consume(p, TOKEN_LEFT_PAREN, "Expected '(' after function name");
    
    int capacity = 4;
    node->function.param_names = malloc(sizeof(char*) * capacity);
    node->function.param_types = malloc(sizeof(char*) * capacity);
    node->function.param_count = 0;
    
    if (!check(p, TOKEN_RIGHT_PAREN)) {
        do {
            if (node->function.param_count >= capacity) {
                capacity *= 2;
                node->function.param_names = realloc(node->function.param_names, sizeof(char*) * capacity);
                node->function.param_types = realloc(node->function.param_types, sizeof(char*) * capacity);
            }
            
            consume(p, TOKEN_IDENTIFIER, "Expected parameter name");
            node->function.param_names[node->function.param_count] = 
                string_copy(p->previous.start, p->previous.length);
            
            consume(p, TOKEN_COLON, "Expected ':' after parameter name");
            
            // Allow type keywords or identifiers as types
            if (!match(p, TOKEN_INT) && !match(p, TOKEN_BOOL) && 
                !match(p, TOKEN_STRING_TYPE) && !match(p, TOKEN_VOID) &&
                !match(p, TOKEN_IDENTIFIER)) {
                parser_error_at(p, &p->current, "Expected parameter type");
            }
            node->function.param_types[node->function.param_count] = 
                string_copy(p->previous.start, p->previous.length);
            
            node->function.param_count++;
        } while (match(p, TOKEN_COMMA));
    }
    
    consume(p, TOKEN_RIGHT_PAREN, "Expected ')' after parameters");
    consume(p, TOKEN_ARROW, "Expected '->' after parameters");
    
    // Allow type keywords or identifiers as return type
    if (!match(p, TOKEN_INT) && !match(p, TOKEN_BOOL) && 
        !match(p, TOKEN_STRING_TYPE) && !match(p, TOKEN_VOID) &&
        !match(p, TOKEN_IDENTIFIER)) {
        parser_error_at(p, &p->current, "Expected return type");
    }
    
    node->function.return_type = string_copy(p->previous.start, p->previous.length);
    
    consume(p, TOKEN_LEFT_BRACE, "Expected '{' before function body");
    node->function.body = block(p);
    
    return node;
}

void parser_init(Parser* p, Lexer* lexer) {
    p->lexer = lexer;
    p->had_error = false;
    p->panic_mode = false;
    advance(p);
}

ASTNode* parse(Parser* p) {
    ASTNode* program = ast_create_node(AST_PROGRAM, 1);
    program->program.functions = malloc(sizeof(ASTNode*) * 4);  // Start small
    program->program.capacity = 4;
    program->program.function_count = 0;
    program->program.enums = malloc(sizeof(ASTNode*) * 4);  // Start small
    program->program.enum_capacity = 4;
    program->program.enum_count = 0;
    
    while (!match(p, TOKEN_EOF)) {
        // Handle top-level enum declarations
        if (match(p, TOKEN_ENUM)) {  // match() consumes the token
            ASTNode* enum_node = enum_decl(p);  // enum_decl expects TOKEN_ENUM already consumed
            
            // Add to program's enum list
            if (program->program.enum_count >= program->program.enum_capacity) {
                program->program.enum_capacity *= 2;
                program->program.enums = realloc(program->program.enums,
                                                sizeof(ASTNode*) * program->program.enum_capacity);
            }
            program->program.enums[program->program.enum_count++] = enum_node;
        } else if (match(p, TOKEN_FUNC)) {
            if (program->program.function_count >= program->program.capacity) {
                program->program.capacity *= 2;
                program->program.functions = realloc(program->program.functions,
                                                    sizeof(ASTNode*) * program->program.capacity);
            }
            program->program.functions[program->program.function_count++] = function_decl(p);
        } else {
            parser_error_at(p, &p->current, "Expected function or enum declaration");
            advance(p);
        }
    }
    
    return program;
}
