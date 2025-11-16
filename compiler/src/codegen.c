#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/compiler.h"

// Symbol table functions
void symtab_init(SymbolTable* table) {
    table->symbols = malloc(sizeof(Symbol) * 16);  // Start smaller
    table->capacity = 16;
    table->count = 0;
    table->scope_depth = 0;
}

void symtab_free(SymbolTable* table) {
    for (int i = 0; i < table->count; i++) {
        free(table->symbols[i].name);
        if (table->symbols[i].type) {
            free(table->symbols[i].type);
        }
    }
    free(table->symbols);
}

void symtab_add(SymbolTable* table, const char* name, int reg, const char* type) {
    if (table->count >= table->capacity) {
        table->capacity *= 2;
        table->symbols = realloc(table->symbols, sizeof(Symbol) * table->capacity);
    }
    
    table->symbols[table->count].name = strdup(name);
    table->symbols[table->count].reg = reg;
    table->symbols[table->count].scope_depth = table->scope_depth;
    table->symbols[table->count].is_const = false;
    table->symbols[table->count].const_value = 0;
    table->symbols[table->count].type = type ? strdup(type) : strdup("int");
    table->count++;
}

void symtab_add_const(SymbolTable* table, const char* name, int64_t value) {
    if (table->count >= table->capacity) {
        table->capacity *= 2;
        table->symbols = realloc(table->symbols, sizeof(Symbol) * table->capacity);
    }
    
    table->symbols[table->count].name = strdup(name);
    table->symbols[table->count].reg = -1;  // No register for constants
    table->symbols[table->count].scope_depth = table->scope_depth;
    table->symbols[table->count].is_const = true;
    table->symbols[table->count].const_value = value;
    table->symbols[table->count].type = strdup("int");
    table->count++;
}

Symbol* symtab_find(SymbolTable* table, const char* name) {
    for (int i = table->count - 1; i >= 0; i--) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return &table->symbols[i];
        }
    }
    return NULL;
}

int symtab_lookup(SymbolTable* table, const char* name) {
    for (int i = table->count - 1; i >= 0; i--) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return table->symbols[i].reg;
        }
    }
    return -1;
}

void symtab_enter_scope(SymbolTable* table) {
    table->scope_depth++;
}

void symtab_exit_scope(SymbolTable* table) {
    // Remove all symbols from current scope
    while (table->count > 0 && table->symbols[table->count - 1].scope_depth == table->scope_depth) {
        free(table->symbols[table->count - 1].name);
        if (table->symbols[table->count - 1].type) {
            free(table->symbols[table->count - 1].type);
        }
        // Note: We don't free the register here because it may still be in use
        // Register allocation is handled separately
        table->count--;
    }
    table->scope_depth--;
}

// Code generator helper functions
// Forward declarations
static void emit(CodeGen* gen, const char* format, ...);

// Helper to emit move operation (MOV doesn't work, use ADD instead)
static void emit_move(CodeGen* gen, int rd, int rs) {
    // If destination and source are the same register, no need to emit
    // any instructions (would otherwise zero the register). This
    // prevents bugs where we clear the syscall argument register (R1)
    // before using it when the allocator returned R1 for the value.
    if (rd == rs) return;

    emit(gen, "    MOVI R%d, 0\n", rd);
    emit(gen, "    ADD R%d, R%d, R%d\n", rd, rd, rs);
}

// Helper to load a 64-bit immediate value into a register
// MOVI can only handle 14-bit signed values, so we use a workaround
// We'll store large constants in memory or build them up piece by piece
static void emit_load_immediate(CodeGen* gen, int rd, uint64_t value, const char* comment) {
    // Check if value fits in 14-bit signed immediate (-8192 to 8191)
    int64_t signed_val = (int64_t)value;
    if (signed_val >= -8192 && signed_val <= 8191) {
        if (comment) {
            emit(gen, "    MOVI R%d, %lld    ; %s\n", rd, signed_val, comment);
        } else {
            emit(gen, "    MOVI R%d, %lld\n", rd, signed_val);
        }
        return;
    }
    
    // For values that don't fit, build them up
    // This is a simplified approach - split into 4 x 16-bit chunks
    if (comment) {
        emit(gen, "    ; Load immediate %llu (0x%llX) - %s\n", value, value, comment);
    }
    
    uint16_t chunk0 = (value >> 0) & 0xFFFF;
    uint16_t chunk1 = (value >> 16) & 0xFFFF;
    uint16_t chunk2 = (value >> 32) & 0xFFFF;
    uint16_t chunk3 = (value >> 48) & 0xFFFF;
    
    // Start with chunk3 (highest bits) using LUI if non-zero
    if (chunk3 != 0) {
        // LUI loads upper 14 bits shifted left by 50
        // So we need to shift our chunk3 appropriately
        emit(gen, "    LUI R%d, %u\n", rd, chunk3 >> 2);  // Shift right 2 to fit in 14 bits
        
        // Now we need to add the remaining bits
        // This is getting complicated - let's use a simpler approach
    }
    
    // Simpler approach: just zero the register for now and document the issue
    emit(gen, "    MOVI R%d, 0\n", rd);
    emit(gen, "    ; TODO: Large immediate value %llu not fully loaded\n", value);
}

static void emit(CodeGen* gen, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(gen->output, format, args);
    va_end(args);
}

static int allocate_register(CodeGen* gen) {
    // Use R1-R30 for temporaries (30 registers)
    // R0 = always zero
    // R1 = syscall argument/return (can be reused when not in syscall)
    // R2 = function return value (can be reused when not returning)
    // R3 = stack pointer
    // R31 = link register
    for (int i = 1; i <= 30; i++) {
        if (i == 3) continue; // Skip R3 (stack pointer)
        if (!gen->reg_in_use[i]) {
            gen->reg_in_use[i] = true;
            return i;
        }
    }
    
    fprintf(stderr, "Error: Out of registers (all 30 allocatable registers in use)\n");
    exit(1);
}

static void free_register(CodeGen* gen, int reg) {
    if (reg >= 1 && reg <= 30 && reg != 3) {
        gen->reg_in_use[reg] = false;
    }
}

static int new_label(CodeGen* gen) {
    return gen->label_count++;
}

static void add_string_literal(CodeGen* gen, const char* str) {
    if (gen->string_count >= gen->string_capacity) {
        gen->string_capacity *= 2;
        gen->strings = realloc(gen->strings, sizeof(char*) * gen->string_capacity);
    }
    gen->strings[gen->string_count++] = strdup(str);
}

// Forward declarations
static int gen_expression(CodeGen* gen, ASTNode* node);

static void gen_statement(CodeGen* gen, ASTNode* node) {
    switch (node->type) {
        case AST_DECLARATION: {
            int reg = allocate_register(gen);
            int value_reg = gen_expression(gen, node->declaration.initializer);
            emit_move(gen, reg, value_reg);
            free_register(gen, value_reg);
            symtab_add(&gen->symtab, node->declaration.name, reg, node->declaration.type);
            break;
        }
        
        case AST_ENUM_DECL: {
            // Enum values are compile-time constants
            // Don't allocate registers, just store the constant values
            for (int i = 0; i < node->enum_decl.value_count; i++) {
                symtab_add_const(&gen->symtab, node->enum_decl.value_names[i], node->enum_decl.values[i]);
            }
            break;
        }
        
        case AST_ASSIGNMENT: {
            Symbol* sym = symtab_find(&gen->symtab, node->assignment.name);
            if (!sym) {
                fprintf(stderr, "Error: Undefined variable '%s'\n", node->assignment.name);
                exit(1);
            }
            if (sym->is_const) {
                fprintf(stderr, "Error: Cannot assign to constant '%s'\n", node->assignment.name);
                exit(1);
            }
            int value_reg = gen_expression(gen, node->assignment.value);
            emit_move(gen, sym->reg, value_reg);
            free_register(gen, value_reg);
            break;
        }
        
        case AST_IF_STMT: {
            int cond_reg = gen_expression(gen, node->if_stmt.condition);
            int else_label = new_label(gen);
            int end_label = new_label(gen);
            
            // Compare with zero (false) using CMP with R0
            emit(gen, "    CMP R%d, R0\n", cond_reg);
            free_register(gen, cond_reg);
            
            if (node->if_stmt.else_branch) {
                emit(gen, "    JZ .L%d\n", else_label);  // Jump to else if zero (false)
                gen_statement(gen, node->if_stmt.then_branch);
                emit(gen, "    JMP .L%d\n", end_label);
                emit(gen, ".L%d:\n", else_label);
                gen_statement(gen, node->if_stmt.else_branch);
                emit(gen, ".L%d:\n", end_label);
            } else {
                emit(gen, "    JZ .L%d\n", end_label);  // Jump to end if zero (false)
                gen_statement(gen, node->if_stmt.then_branch);
                emit(gen, ".L%d:\n", end_label);
            }
            break;
        }
        
        case AST_WHILE_STMT: {
            int start_label = new_label(gen);
            int end_label = new_label(gen);
            
            int prev_loop_start = gen->loop_start;
            int prev_loop_end = gen->loop_end;
            gen->loop_start = start_label;
            gen->loop_end = end_label;
            
            emit(gen, ".L%d:\n", start_label);
            int cond_reg = gen_expression(gen, node->while_stmt.condition);
            emit(gen, "    CMP R%d, R0\n", cond_reg);
            free_register(gen, cond_reg);
            emit(gen, "    JZ .L%d\n", end_label);  // Jump to end if zero (false)
            
            gen_statement(gen, node->while_stmt.body);
            
            emit(gen, "    JMP .L%d\n", start_label);
            emit(gen, ".L%d:\n", end_label);
            
            gen->loop_start = prev_loop_start;
            gen->loop_end = prev_loop_end;
            break;
        }
        
        case AST_DO_WHILE_STMT: {
            int start_label = new_label(gen);
            int continue_label = new_label(gen);
            int end_label = new_label(gen);
            
            int prev_loop_start = gen->loop_start;
            int prev_loop_end = gen->loop_end;
            gen->loop_start = continue_label;
            gen->loop_end = end_label;
            
            emit(gen, ".L%d:\n", start_label);
            gen_statement(gen, node->do_while_stmt.body);
            
            emit(gen, ".L%d:\n", continue_label);
            int cond_reg = gen_expression(gen, node->do_while_stmt.condition);
            emit(gen, "    CMP R%d, R0\n", cond_reg);
            free_register(gen, cond_reg);
            emit(gen, "    JNZ .L%d\n", start_label);  // Jump back if non-zero (true)
            emit(gen, ".L%d:\n", end_label);
            
            gen->loop_start = prev_loop_start;
            gen->loop_end = prev_loop_end;
            break;
        }
        
        case AST_FOR_STMT: {
            if (node->for_stmt.init) {
                gen_statement(gen, node->for_stmt.init);
            }
            
            int start_label = new_label(gen);
            int end_label = new_label(gen);
            int continue_label = new_label(gen);
            
            int prev_loop_start = gen->loop_start;
            int prev_loop_end = gen->loop_end;
            gen->loop_start = continue_label;
            gen->loop_end = end_label;
            
            emit(gen, ".L%d:\n", start_label);
            
            if (node->for_stmt.condition) {
                int cond_reg = gen_expression(gen, node->for_stmt.condition);
                emit(gen, "    CMP R%d, R0\n", cond_reg);
                free_register(gen, cond_reg);
                emit(gen, "    JZ .L%d\n", end_label);  // Jump to end if zero (false)
            }
            
            gen_statement(gen, node->for_stmt.body);
            
            emit(gen, ".L%d:\n", continue_label);
            if (node->for_stmt.increment) {
                gen_statement(gen, node->for_stmt.increment);
            }
            
            emit(gen, "    JMP .L%d\n", start_label);
            emit(gen, ".L%d:\n", end_label);
            
            gen->loop_start = prev_loop_start;
            gen->loop_end = prev_loop_end;
            break;
        }
        
        case AST_SWITCH_STMT: {
            // Evaluate switch expression
            int switch_reg = gen_expression(gen, node->switch_stmt.expression);
            
            // Generate labels for each case and for end
            int end_label = new_label(gen);
            int default_label = -1;
            
            // Save previous loop state
            int prev_loop_end = gen->loop_end;
            gen->loop_end = end_label;  // break jumps to end of switch
            
            // First pass: generate case comparisons and jumps
            ASTNode* body = node->switch_stmt.body;
            int* case_labels = malloc(sizeof(int) * body->block.statement_count);
            
            for (int i = 0; i < body->block.statement_count; i++) {
                ASTNode* stmt = body->block.statements[i];
                case_labels[i] = new_label(gen);
                
                if (stmt->type == AST_CASE_STMT) {
                    // Compare switch value with case value
                    emit(gen, "    MOVI R%d, %ld\n", switch_reg + 1, stmt->case_stmt.value);
                    emit(gen, "    CMP R%d, R%d\n", switch_reg, switch_reg + 1);
                    emit(gen, "    JZ .L%d\n", case_labels[i]);  // Jump if equal
                } else if (stmt->type == AST_DEFAULT_STMT) {
                    default_label = case_labels[i];
                }
            }
            
            // If no case matched, jump to default or end
            if (default_label != -1) {
                emit(gen, "    JMP .L%d\n", default_label);
            } else {
                emit(gen, "    JMP .L%d\n", end_label);
            }
            
            free_register(gen, switch_reg);
            
            // Second pass: generate case bodies
            for (int i = 0; i < body->block.statement_count; i++) {
                ASTNode* stmt = body->block.statements[i];
                emit(gen, ".L%d:\n", case_labels[i]);
                
                if (stmt->type == AST_CASE_STMT) {
                    gen_statement(gen, stmt->case_stmt.body);
                } else if (stmt->type == AST_DEFAULT_STMT) {
                    gen_statement(gen, stmt->default_stmt.body);
                }
                // Note: Fall-through is automatic - no jump unless there's a break
            }
            
            emit(gen, ".L%d:\n", end_label);
            
            free(case_labels);
            gen->loop_end = prev_loop_end;
            break;
        }
        
        case AST_RETURN_STMT: {
            if (node->return_stmt.value) {
                int reg = gen_expression(gen, node->return_stmt.value);
                emit_move(gen, 2, reg);  // R2 = return value register
                free_register(gen, reg);
            }
            // Don't emit RET here - it will be handled by gen_function
            break;
        }
        
        case AST_GOTO_STMT: {
            // Emit jump to user-defined label
            emit(gen, "    JMP .%s\n", node->goto_stmt.label);
            break;
        }
        
        case AST_LABEL_STMT: {
            // Emit user-defined label
            emit(gen, ".%s:\n", node->label_stmt.name);
            // Generate code for the statement after the label
            if (node->label_stmt.statement) {
                gen_statement(gen, node->label_stmt.statement);
            }
            break;
        }
        
        case AST_BLOCK: {
            symtab_enter_scope(&gen->symtab);
            for (int i = 0; i < node->block.statement_count; i++) {
                gen_statement(gen, node->block.statements[i]);
            }
            symtab_exit_scope(&gen->symtab);
            break;
        }
        
        case AST_EXPRESSION_STMT: {
            int reg = gen_expression(gen, node->expr_stmt.expression);
            free_register(gen, reg);
            break;
        }
        
        case AST_BREAK: {
            if (gen->loop_end == -1) {
                fprintf(stderr, "Error: 'break' outside loop\n");
                exit(1);
            }
            emit(gen, "    JMP .L%d\n", gen->loop_end);
            break;
        }
        
        case AST_CONTINUE: {
            if (gen->loop_start == -1) {
                fprintf(stderr, "Error: 'continue' outside loop\n");
                exit(1);
            }
            emit(gen, "    JMP .L%d\n", gen->loop_start);
            break;
        }
        
        default:
            fprintf(stderr, "Error: Unknown statement type\n");
            break;
    }
}

// Helper function to get the type of an expression
static const char* get_expr_type(CodeGen* gen, ASTNode* node) {
    switch (node->type) {
        case AST_LITERAL_INT:
            return "int";
        case AST_LITERAL_FLOAT:
            return "float";
        case AST_LITERAL_DOUBLE:
            return "double";
        case AST_LITERAL_BOOL:
            return "bool";
        case AST_IDENTIFIER: {
            Symbol* sym = symtab_find(&gen->symtab, node->identifier.name);
            if (sym && sym->type) {
                return sym->type;
            }
            return "int";  // default
        }
        case AST_BINARY_OP: {
            // For binary ops, use the type of the left operand
            return get_expr_type(gen, node->binary.left);
        }
        default:
            return "int";  // default
    }
}

static int gen_expression(CodeGen* gen, ASTNode* node) {
    int reg, left_reg, right_reg;
    
    switch (node->type) {
        case AST_SIZEOF: {
            // sizeof is evaluated at compile time
            int size = 8;  // Default to 8 bytes (64-bit)
            
            if (node->sizeof_expr.type_name) {
                // sizeof(type)
                if (strcmp(node->sizeof_expr.type_name, "char") == 0) {
                    size = 1;
                } else if (strcmp(node->sizeof_expr.type_name, "short") == 0) {
                    size = 2;
                } else if (strcmp(node->sizeof_expr.type_name, "int") == 0) {
                    size = 8;  // 64-bit int
                } else if (strcmp(node->sizeof_expr.type_name, "long") == 0) {
                    size = 8;
                } else if (strcmp(node->sizeof_expr.type_name, "bool") == 0) {
                    size = 1;
                } else if (strcmp(node->sizeof_expr.type_name, "float") == 0) {
                    size = 4;
                } else if (strcmp(node->sizeof_expr.type_name, "double") == 0) {
                    size = 8;
                } else {
                    size = 8;  // Default
                }
            } else {
                // sizeof(expression) - for now, all expressions are 64-bit
                // We could evaluate the expression type in the future
                size = 8;
            }
            
            reg = allocate_register(gen);
            emit(gen, "    MOVI R%d, %d\n", reg, size);
            return reg;
        }
        
        case AST_LITERAL_INT: {
            reg = allocate_register(gen);
            emit(gen, "    MOVI R%d, %lld\n", reg, node->integer.value);
            return reg;
        }
        
        case AST_LITERAL_FLOAT: {
            // PRAGMATIC APPROACH: Store float as scaled integer (x1000)
            // Since A1M doesn't have FPU and MOVI is limited to 14-bit immediates,
            // we use fixed-point arithmetic: 2.5 becomes 2500
            reg = allocate_register(gen);
            int64_t scaled = (int64_t)(node->float_literal.value * 1000.0f);
            emit(gen, "    MOVI R%d, %lld    ; float %f (stored as scaled int x1000)\n", 
                 reg, scaled, node->float_literal.value);
            return reg;
        }
        
        case AST_LITERAL_DOUBLE: {
            // PRAGMATIC APPROACH: Store double as scaled integer (x1000)
            reg = allocate_register(gen);
            int64_t scaled = (int64_t)(node->double_literal.value * 1000.0);
            emit(gen, "    MOVI R%d, %lld    ; double %f (stored as scaled int x1000)\n", 
                 reg, scaled, node->double_literal.value);
            return reg;
        }
        
        case AST_LITERAL_BOOL: {
            reg = allocate_register(gen);
            emit(gen, "    MOVI R%d, %d\n", reg, node->boolean.value ? 1 : 0);
            return reg;
        }
        
        case AST_IDENTIFIER: {
            Symbol* sym = symtab_find(&gen->symtab, node->identifier.name);
            if (!sym) {
                fprintf(stderr, "Error: Undefined variable '%s'\n", node->identifier.name);
                exit(1);
            }
            
            reg = allocate_register(gen);
            if (sym->is_const) {
                // For constants, emit the value directly
                emit(gen, "    MOVI R%d, %lld\n", reg, sym->const_value);
            } else {
                // For variables, copy from the variable's register
                emit_move(gen, reg, sym->reg);
            }
            return reg;
        }
        
        case AST_BINARY_OP: {
            left_reg = gen_expression(gen, node->binary.left);
            right_reg = gen_expression(gen, node->binary.right);
            
            // Determine if we're dealing with floating-point types
            const char* left_type = get_expr_type(gen, node->binary.left);
            const char* right_type = get_expr_type(gen, node->binary.right);
            bool is_float_op = (strcmp(left_type, "float") == 0 || strcmp(left_type, "double") == 0 ||
                               strcmp(right_type, "float") == 0 || strcmp(right_type, "double") == 0);
            
            switch (node->binary.op) {
                case TOKEN_PLUS:
                    if (is_float_op) {
                        // Float addition: (a*1000) + (b*1000) = (a+b)*1000
                        emit(gen, "    ; Float addition (scaled integers)\n");
                        emit(gen, "    ADD R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    } else {
                        emit(gen, "    ADD R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    }
                    break;
                case TOKEN_MINUS:
                    if (is_float_op) {
                        // Float subtraction: (a*1000) - (b*1000) = (a-b)*1000
                        emit(gen, "    ; Float subtraction (scaled integers)\n");
                        emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    } else {
                        emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    }
                    break;
                case TOKEN_STAR:
                    if (is_float_op) {
                        // Float multiplication: (a*1000) * (b*1000) / 1000 = (a*b)*1000
                        emit(gen, "    ; Float multiplication (scaled integers)\n");
                        emit(gen, "    MUL R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        // Reuse right_reg for the scale factor
                        emit(gen, "    MOVI R%d, 1000\n", right_reg);
                        emit(gen, "    DIV R%d, R%d, R%d    ; Divide by scale factor\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    } else {
                        emit(gen, "    MUL R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    }
                    break;
                case TOKEN_SLASH:
                    if (is_float_op) {
                        // Float division: (a*1000) * 1000 / (b*1000) = (a/b)*1000
                        emit(gen, "    ; Float division (scaled integers)\n");
                        int temp_reg = allocate_register(gen);
                        emit(gen, "    MOVI R%d, 1000\n", temp_reg);
                        emit(gen, "    MUL R%d, R%d, R%d    ; Multiply by scale factor\n", left_reg, left_reg, temp_reg);
                        emit(gen, "    DIV R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, temp_reg);
                        free_register(gen, right_reg);
                    } else {
                        emit(gen, "    DIV R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                        free_register(gen, right_reg);
                    }
                    break;
                case TOKEN_PERCENT:
                    emit(gen, "    MOD R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    break;
                case TOKEN_AMPERSAND:
                    emit(gen, "    AND R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    break;
                case TOKEN_PIPE:
                    emit(gen, "    OR R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    break;
                case TOKEN_CARET:
                    emit(gen, "    XOR R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    break;
                case TOKEN_LEFT_SHIFT:
                    emit(gen, "    SHL R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    break;
                case TOKEN_RIGHT_SHIFT:
                    emit(gen, "    SHR R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    break;
                case TOKEN_EQUAL_EQUAL: {
                    // a == b: SUB temp, a, b; result = (temp == 0)
                    emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    int zero_label = new_label(gen);
                    int end_label = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JZ .L%d\n", zero_label);
                    // Not equal: set to 0
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    JMP .L%d\n", end_label);
                    // Equal: set to 1
                    emit(gen, ".L%d:\n", zero_label);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", end_label);
                    break;
                }
                case TOKEN_BANG_EQUAL: {
                    // a != b: SUB temp, a, b; result = (temp != 0)
                    emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    int nonzero_label = new_label(gen);
                    int end_label = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JNZ .L%d\n", nonzero_label);
                    // Equal: set to 0
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    JMP .L%d\n", end_label);
                    // Not equal: set to 1
                    emit(gen, ".L%d:\n", nonzero_label);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", end_label);
                    break;
                }
                case TOKEN_LESS: {
                    // a < b: CMP a, b; result = (a - b < 0)
                    emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    int neg_label = new_label(gen);
                    int end_label = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JN .L%d\n", neg_label);  // Jump if negative
                    // Not less: set to 0
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    JMP .L%d\n", end_label);
                    // Less: set to 1
                    emit(gen, ".L%d:\n", neg_label);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", end_label);
                    break;
                }
                case TOKEN_LESS_EQUAL: {
                    // a <= b: equivalent to !(a > b) or (a - b <= 0)
                    // We use: a - b < 0 OR a - b == 0
                    emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    int neg_or_zero_label = new_label(gen);
                    int end_label = new_label(gen);
                    // Check if negative first
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JN .L%d\n", neg_or_zero_label);  // Jump if negative
                    // Check if zero
                    emit(gen, "    JZ .L%d\n", neg_or_zero_label);  // Jump if zero
                    // Greater than: set to 0
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    JMP .L%d\n", end_label);
                    // Less or equal: set to 1
                    emit(gen, ".L%d:\n", neg_or_zero_label);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", end_label);
                    break;
                }
                case TOKEN_GREATER: {
                    // a > b: equivalent to b < a
                    emit(gen, "    SUB R%d, R%d, R%d\n", right_reg, right_reg, left_reg);
                    int neg_label = new_label(gen);
                    int end_label = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", right_reg);
                    emit(gen, "    JN .L%d\n", neg_label);  // Jump if negative
                    // Not greater: set to 0
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    JMP .L%d\n", end_label);
                    // Greater: set to 1
                    emit(gen, ".L%d:\n", neg_label);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", end_label);
                    break;
                }
                case TOKEN_GREATER_EQUAL: {
                    // a >= b: equivalent to !(a < b) or (a - b >= 0)
                    // We use: a - b > 0 OR a - b == 0
                    emit(gen, "    SUB R%d, R%d, R%d\n", left_reg, left_reg, right_reg);
                    int ge_or_zero_label = new_label(gen);
                    int check_zero_label = new_label(gen);
                    int end_label = new_label(gen);
                    // Check if negative
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JN .L%d\n", end_label);  // If negative, jump to end (set to 0)
                    // Not negative, so >= 0, which means a >= b
                    emit(gen, "    JMP .L%d\n", ge_or_zero_label);
                    // Less: set to 0
                    emit(gen, ".L%d:\n", end_label);
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    JMP .L%d\n", check_zero_label);
                    // Greater or equal: set to 1
                    emit(gen, ".L%d:\n", ge_or_zero_label);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", check_zero_label);
                    break;
                }
                case TOKEN_AMPERSAND_AMPERSAND: {
                    // a && b: if a is false, result is false; otherwise result = b
                    int short_circuit = new_label(gen);
                    int end = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JZ .L%d\n", short_circuit);  // If left is 0 (false), short-circuit
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    ADD R%d, R%d, R%d\n", left_reg, left_reg, right_reg);  // left_reg = right_reg
                    emit(gen, "    JMP .L%d\n", end);
                    emit(gen, ".L%d:\n", short_circuit);
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, ".L%d:\n", end);
                    break;
                }
                case TOKEN_PIPE_PIPE: {
                    // a || b: if a is true, result is true; otherwise result = b
                    int short_circuit = new_label(gen);
                    int end = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", left_reg);
                    emit(gen, "    JNZ .L%d\n", short_circuit);  // If left is non-zero (true), short-circuit
                    emit(gen, "    MOVI R%d, 0\n", left_reg);
                    emit(gen, "    ADD R%d, R%d, R%d\n", left_reg, left_reg, right_reg);  // left_reg = right_reg
                    emit(gen, "    JMP .L%d\n", end);
                    emit(gen, ".L%d:\n", short_circuit);
                    emit(gen, "    MOVI R%d, 1\n", left_reg);
                    emit(gen, ".L%d:\n", end);
                    break;
                }
                default:
                    fprintf(stderr, "Error: Unknown binary operator\n");
                    break;
            }
            
            free_register(gen, right_reg);
            return left_reg;
        }
        
        case AST_UNARY_OP: {
            reg = gen_expression(gen, node->unary.operand);
            
            switch (node->unary.op) {
                case TOKEN_MINUS:
                    // Negate: 0 - reg
                    emit(gen, "    SUB R%d, R0, R%d\n", reg, reg);
                    break;
                case TOKEN_BANG: {
                    // Logical NOT: if reg == 0 then 1 else 0
                    int zero_label = new_label(gen);
                    int end_label = new_label(gen);
                    emit(gen, "    CMP R%d, R0\n", reg);
                    emit(gen, "    JZ .L%d\n", zero_label);
                    // Non-zero: set to 0
                    emit(gen, "    MOVI R%d, 0\n", reg);
                    emit(gen, "    JMP .L%d\n", end_label);
                    // Zero: set to 1
                    emit(gen, ".L%d:\n", zero_label);
                    emit(gen, "    MOVI R%d, 1\n", reg);
                    emit(gen, ".L%d:\n", end_label);
                    break;
                }
                case TOKEN_TILDE:
                    // Bitwise NOT
                    emit(gen, "    NOT R%d, R%d\n", reg, reg);
                    break;
                case TOKEN_AMPERSAND: {
                    // Address-of operator: &x
                    // For variables in registers, we can't truly get an address
                    // This is a placeholder - would need stack allocation for full support
                    if (node->unary.operand->type != AST_IDENTIFIER) {
                        fprintf(stderr, "Error: Can only take address of variables\n");
                        exit(1);
                    }
                    fprintf(stderr, "Warning: Address-of operator not fully supported yet (variables in registers)\n");
                    // Return a pseudo-address (the register number itself as a marker)
                    emit(gen, "    MOVI R%d, 0xDEAD\n", reg);  // Placeholder
                    break;
                }
                case TOKEN_STAR: {
                    // Dereference operator: *ptr
                    // This would need LOAD instruction
                    fprintf(stderr, "Warning: Dereference operator not fully supported yet\n");
                    // Placeholder: just return the value
                    // In reality, we'd do: LOAD reg, 0(ptr_reg)
                    break;
                }
                case TOKEN_PLUS_PLUS: {
                    // Prefix increment: ++x
                    // Must be an identifier (variable)
                    if (node->unary.operand->type != AST_IDENTIFIER) {
                        fprintf(stderr, "Error: Can only increment variables\n");
                        exit(1);
                    }
                    const char* var_name = node->unary.operand->identifier.name;
                    Symbol* sym = symtab_find(&gen->symtab, var_name);
                    if (!sym) {
                        fprintf(stderr, "Error: Undefined variable '%s'\n", var_name);
                        exit(1);
                    }
                    if (sym->is_const) {
                        fprintf(stderr, "Error: Cannot increment constant '%s'\n", var_name);
                        exit(1);
                    }
                    // Increment the variable: var_reg = var_reg + 1
                    emit(gen, "    MOVI R%d, 1\n", reg);
                    emit(gen, "    ADD R%d, R%d, R%d\n", sym->reg, sym->reg, reg);
                    // Return the new value
                    emit_move(gen, reg, sym->reg);
                    break;
                }
                case TOKEN_MINUS_MINUS: {
                    // Prefix decrement: --x
                    if (node->unary.operand->type != AST_IDENTIFIER) {
                        fprintf(stderr, "Error: Can only decrement variables\n");
                        exit(1);
                    }
                    const char* var_name = node->unary.operand->identifier.name;
                    Symbol* sym = symtab_find(&gen->symtab, var_name);
                    if (!sym) {
                        fprintf(stderr, "Error: Undefined variable '%s'\n", var_name);
                        exit(1);
                    }
                    if (sym->is_const) {
                        fprintf(stderr, "Error: Cannot decrement constant '%s'\n", var_name);
                        exit(1);
                    }
                    // Decrement the variable: var_reg = var_reg - 1
                    emit(gen, "    MOVI R%d, 1\n", reg);
                    emit(gen, "    SUB R%d, R%d, R%d\n", sym->reg, sym->reg, reg);
                    // Return the new value
                    emit_move(gen, reg, sym->reg);
                    break;
                }
                default:
                    fprintf(stderr, "Error: Unknown unary operator\n");
                    break;
            }
            
            return reg;
        }
        
        case AST_POSTFIX_OP: {
            // Postfix increment/decrement: x++, x--
            // Must be an identifier (variable)
            if (node->postfix.operand->type != AST_IDENTIFIER) {
                fprintf(stderr, "Error: Can only apply postfix operators to variables\n");
                exit(1);
            }
            
            const char* var_name = node->postfix.operand->identifier.name;
            Symbol* sym = symtab_find(&gen->symtab, var_name);
            if (!sym) {
                fprintf(stderr, "Error: Undefined variable '%s'\n", var_name);
                exit(1);
            }
            if (sym->is_const) {
                fprintf(stderr, "Error: Cannot modify constant '%s'\n", var_name);
                exit(1);
            }
            
            reg = allocate_register(gen);
            
            // Save the old value
            emit_move(gen, reg, sym->reg);
            
            // Modify the variable
            int temp_reg = allocate_register(gen);
            emit(gen, "    MOVI R%d, 1\n", temp_reg);
            
            if (node->postfix.op == TOKEN_PLUS_PLUS) {
                emit(gen, "    ADD R%d, R%d, R%d\n", sym->reg, sym->reg, temp_reg);
            } else { // TOKEN_MINUS_MINUS
                emit(gen, "    SUB R%d, R%d, R%d\n", sym->reg, sym->reg, temp_reg);
            }
            
            free_register(gen, temp_reg);
            
            // Return the old value
            return reg;
        }
        
        case AST_TERNARY_OP: {
            // Ternary operator: condition ? true_expr : false_expr
            int false_label = new_label(gen);
            int end_label = new_label(gen);
            
            // Evaluate condition
            int cond_reg = gen_expression(gen, node->ternary_op.condition);
            emit(gen, "    CMP R%d, R0\n", cond_reg);
            free_register(gen, cond_reg);
            
            // Jump to false expression if condition is zero
            emit(gen, "    JZ .L%d\n", false_label);
            
            // Evaluate true expression
            int result_reg = gen_expression(gen, node->ternary_op.true_expr);
            emit(gen, "    JMP .L%d\n", end_label);
            
            // Evaluate false expression
            emit(gen, ".L%d:\n", false_label);
            int false_reg = gen_expression(gen, node->ternary_op.false_expr);
            
            // Move false result to result register if they're different
            if (result_reg != false_reg) {
                emit(gen, "    ADD R%d, R%d, R0\n", result_reg, false_reg);
                free_register(gen, false_reg);
            }
            
            emit(gen, ".L%d:\n", end_label);
            return result_reg;
        }
        
        case AST_CALL: {
            // Handle built-in functions
            if (strcmp(node->call.name, "print") == 0) {
                if (node->call.arg_count != 1) {
                    fprintf(stderr, "Error: print() takes exactly 1 argument\n");
                    exit(1);
                }
                
                // Determine type based on argument
                if (node->call.args[0]->type == AST_LITERAL_STRING) {
                    // For string literals, emit character-by-character syscalls
                    const char* str = node->call.args[0]->string.value;
                    for (int i = 0; str[i] != '\0'; i++) {
                        int char_code;
                        // Handle escape sequences
                        if (str[i] == '\\' && str[i + 1] != '\0') {
                            i++; // Skip backslash
                            switch (str[i]) {
                                case 'n': char_code = 10; break;  // newline
                                case 't': char_code = 9; break;   // tab
                                case 'r': char_code = 13; break;  // carriage return
                                case '\\': char_code = '\\'; break; // backslash
                                case '"': char_code = '"'; break;  // double quote
                                case '0': char_code = 0; break;    // null
                                default: char_code = str[i]; break; // treat as literal
                            }
                        } else {
                            char_code = (unsigned char)str[i];
                        }
                        emit(gen, "    MOVI R1, %d\n", char_code);
                        emit(gen, "    SYSCALL 0x02\n");  // print_char
                    }
                } else {
                    int arg_reg = gen_expression(gen, node->call.args[0]);
                    // Check if the argument is a float/double type
                    const char* arg_type = get_expr_type(gen, node->call.args[0]);
                    bool is_float = (strcmp(arg_type, "float") == 0 || strcmp(arg_type, "double") == 0);
                    
                    // If the expression result is already in R1, don't clear it
                    // before adding — clearing would zero the value.
                    if (arg_reg != 1) {
                        emit(gen, "    MOVI R1, 0\n");  // Clear R1
                        emit(gen, "    ADD R1, R1, R%d\n", arg_reg);  // R1 = R1 + arg_reg
                    }
                    
                    if (is_float) {
                        emit(gen, "    SYSCALL 0x05\n");  // print_float
                    } else {
                        emit(gen, "    SYSCALL 0x01\n");  // print_int
                    }
                    free_register(gen, arg_reg);
                }
                
                reg = allocate_register(gen);
                emit(gen, "    MOVI R%d, 0\n", reg);
                return reg;
            } else if (strcmp(node->call.name, "input") == 0) {
                emit(gen, "    SYSCALL 0x03\n");  // read_int
                reg = allocate_register(gen);
                emit_move(gen, reg, 1);
                return reg;
            } else {
                // User-defined function call
                
                // Save caller-saved registers (R16-R30) before call
                // These might be clobbered by the callee
                emit(gen, "    ; Save caller-saved registers\n");
                for (int i = 16; i <= 30; i++) {
                    if (gen->reg_in_use[i]) {
                        emit(gen, "    PUSH R%d\n", i);
                    }
                }
                
                // Prepare arguments in R1, R2, etc.
                for (int i = 0; i < node->call.arg_count; i++) {
                    int arg_reg = gen_expression(gen, node->call.args[i]);
                    emit_move(gen, i + 1, arg_reg);
                    free_register(gen, arg_reg);
                }
                
                emit(gen, "    CALL %s\n", node->call.name);
                
                // Restore caller-saved registers in reverse order
                emit(gen, "    ; Restore caller-saved registers\n");
                for (int i = 30; i >= 16; i--) {
                    if (gen->reg_in_use[i]) {
                        emit(gen, "    POP R%d\n", i);
                    }
                }
                
                reg = allocate_register(gen);
                emit_move(gen, reg, 2);  // R2 = return value register
                return reg;
            }
        }
        
        default:
            fprintf(stderr, "Error: Unknown expression type\n");
            exit(1);
    }
}

static void gen_function(CodeGen* gen, ASTNode* func) {
    emit(gen, "%s:\n", func->function.name);
    
    bool is_main = (strcmp(func->function.name, "main") == 0);
    
    if (!is_main) {
        // Function prologue: save return address (R31) on stack
        emit(gen, "    PUSH R31\n");
        
        // Save callee-saved registers R4-R15 if they might be used
        // For simplicity, we'll save all of them
        for (int i = 4; i <= 15; i++) {
            emit(gen, "    PUSH R%d\n", i);
        }
    }
    
    // Map parameters to registers (they come in R1-RN)
    for (int i = 0; i < func->function.param_count; i++) {
        int reg = allocate_register(gen);
        emit_move(gen, reg, i + 1);
        symtab_add(&gen->symtab, func->function.param_names[i], reg, func->function.param_types[i]);
    }
    
    // Generate function body
    gen_statement(gen, func->function.body);
    
    // Function epilogue
    if (is_main) {
        emit(gen, "    SYSCALL 0x00\n");  // exit
    } else {
        // Restore callee-saved registers in reverse order
        for (int i = 15; i >= 4; i--) {
            emit(gen, "    POP R%d\n", i);
        }
        
        // Restore return address and return
        emit(gen, "    POP R31\n");
        emit(gen, "    RET\n");
    }
    
    // Clean up symbols
    for (int i = 0; i < func->function.param_count; i++) {
        free_register(gen, symtab_lookup(&gen->symtab, func->function.param_names[i]));
    }
}

void codegen_init(CodeGen* gen, FILE* output) {
    gen->output = output;
    gen->label_count = 0;
    gen->loop_start = -1;
    gen->loop_end = -1;
    gen->strings = malloc(sizeof(char*) * 4);  // Start with minimal capacity
    gen->string_capacity = 4;
    gen->string_count = 0;
    
    for (int i = 0; i < 32; i++) {
        gen->reg_in_use[i] = false;
    }
    
    symtab_init(&gen->symtab);
}

void codegen_free(CodeGen* gen) {
    for (int i = 0; i < gen->string_count; i++) {
        free(gen->strings[i]);
    }
    free(gen->strings);
    symtab_free(&gen->symtab);
}

void generate(CodeGen* gen, ASTNode* program) {
    // Generate header
    emit(gen, "; Generated by A1M Algo Compiler\n");
    emit(gen, ".text\n\n");
    
    // NOTE: Floating-point library functions removed since we're using inline operations
    // Float/double values are stored as scaled integers (x1000) for simplicity
    
    // Process top-level enums first (register global constants)
    for (int i = 0; i < program->program.enum_count; i++) {
        ASTNode* enum_node = program->program.enums[i];
        // Register enum constants in symbol table
        for (int j = 0; j < enum_node->enum_decl.value_count; j++) {
            symtab_add_const(&gen->symtab, 
                           enum_node->enum_decl.value_names[j],
                           enum_node->enum_decl.values[j]);
        }
    }
    
    // Find main function
    int main_idx = -1;
    for (int i = 0; i < program->program.function_count; i++) {
        if (strcmp(program->program.functions[i]->function.name, "main") == 0) {
            main_idx = i;
            break;
        }
    }
    
    if (main_idx < 0) {
        fprintf(stderr, "Error: No main function found\n");
        exit(1);
    }
    
    // Add entry point: jump to main
    emit(gen, "    JMP main\n");
    emit(gen, "\n");
    
    // Generate all non-main functions first
    for (int i = 0; i < program->program.function_count; i++) {
        if (i != main_idx) {
            gen_function(gen, program->program.functions[i]);
        }
    }
    
    // Generate main function last
    gen_function(gen, program->program.functions[main_idx]);
}
