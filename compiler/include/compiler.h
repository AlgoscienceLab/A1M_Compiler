#ifndef ALGO_COMPILER_H
#define ALGO_COMPILER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

// Token Types
typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,
    
    // Preprocessor
    TOKEN_INCLUDE,
    
    // Literals
    TOKEN_INTEGER,
    TOKEN_FLOAT_LITERAL,
    TOKEN_DOUBLE_LITERAL,
    TOKEN_STRING,
    TOKEN_TRUE,
    TOKEN_FALSE,
    
    // Identifiers and keywords
    TOKEN_IDENTIFIER,
    TOKEN_FUNC,
    TOKEN_RETURN,
    TOKEN_LET,
    TOKEN_CONST,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_DO,
    TOKEN_SWITCH,
    TOKEN_CASE,
    TOKEN_DEFAULT,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_GOTO,
    TOKEN_SIZEOF,
    TOKEN_TYPEDEF,
    TOKEN_ENUM,
    TOKEN_STRUCT,
    TOKEN_UNION,
    TOKEN_STATIC,
    TOKEN_EXTERN,
    TOKEN_REGISTER,
    TOKEN_VOLATILE,
    TOKEN_AUTO,
    TOKEN_SIGNED,
    TOKEN_UNSIGNED,
    TOKEN_CHAR,
    TOKEN_SHORT,
    TOKEN_LONG,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    
    // Types
    TOKEN_INT,
    TOKEN_STRING_TYPE,
    TOKEN_BOOL,
    TOKEN_VOID,
    
    // Operators
    TOKEN_PLUS,              // +
    TOKEN_PLUS_PLUS,         // ++
    TOKEN_MINUS,             // -
    TOKEN_MINUS_MINUS,       // --
    TOKEN_STAR,              // *
    TOKEN_SLASH,             // /
    TOKEN_PERCENT,           // %
    TOKEN_EQUAL,             // =
    TOKEN_EQUAL_EQUAL,       // ==
    TOKEN_BANG,              // !
    TOKEN_BANG_EQUAL,        // !=
    TOKEN_LESS,              // <
    TOKEN_LESS_EQUAL,        // <=
    TOKEN_GREATER,           // >
    TOKEN_GREATER_EQUAL,     // >=
    TOKEN_AMPERSAND,         // &
    TOKEN_AMPERSAND_AMPERSAND, // &&
    TOKEN_PIPE,              // |
    TOKEN_PIPE_PIPE,         // ||
    TOKEN_CARET,             // ^
    TOKEN_TILDE,             // ~
    TOKEN_LEFT_SHIFT,        // <<
    TOKEN_RIGHT_SHIFT,       // >>
    
    // Compound assignments
    TOKEN_PLUS_EQUAL,        // +=
    TOKEN_MINUS_EQUAL,       // -=
    TOKEN_STAR_EQUAL,        // *=
    TOKEN_SLASH_EQUAL,       // /=
    TOKEN_PERCENT_EQUAL,     // %=
    TOKEN_AMPERSAND_EQUAL,   // &=
    TOKEN_PIPE_EQUAL,        // |=
    TOKEN_CARET_EQUAL,       // ^=
    TOKEN_LEFT_SHIFT_EQUAL,  // <<=
    TOKEN_RIGHT_SHIFT_EQUAL, // >>=
    
    // Punctuation
    TOKEN_LEFT_PAREN,        // (
    TOKEN_RIGHT_PAREN,       // )
    TOKEN_LEFT_BRACE,        // {
    TOKEN_RIGHT_BRACE,       // }
    TOKEN_LEFT_BRACKET,      // [
    TOKEN_RIGHT_BRACKET,     // ]
    TOKEN_COMMA,             // ,
    TOKEN_SEMICOLON,         // ;
    TOKEN_COLON,             // :
    TOKEN_QUESTION,          // ?
    TOKEN_DOT,               // .
    TOKEN_ARROW,             // ->
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    const char* start;
    int length;
    int line;
} Token;

// Lexer structure
typedef struct {
    const char* start;
    const char* current;
    int line;
} Lexer;

// AST Node Types
typedef enum {
    AST_PROGRAM,
    AST_FUNCTION,
    AST_BLOCK,
    AST_DECLARATION,
    AST_ASSIGNMENT,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_DO_WHILE_STMT,
    AST_FOR_STMT,
    AST_SWITCH_STMT,
    AST_CASE_STMT,
    AST_DEFAULT_STMT,
    AST_GOTO_STMT,
    AST_LABEL_STMT,
    AST_RETURN_STMT,
    AST_EXPRESSION_STMT,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_POSTFIX_OP,
    AST_TERNARY_OP,
    AST_CALL,
    AST_LITERAL_INT,
    AST_LITERAL_FLOAT,
    AST_LITERAL_DOUBLE,
    AST_LITERAL_STRING,
    AST_LITERAL_BOOL,
    AST_LITERAL_CHAR,
    AST_IDENTIFIER,
    AST_BREAK,
    AST_CONTINUE,
    AST_SIZEOF,
    AST_CAST,
    AST_ENUM_DECL,
    AST_STRUCT_DECL,
    AST_MEMBER_ACCESS,
} ASTNodeType;

// Forward declaration
typedef struct ASTNode ASTNode;

// AST Node structure
struct ASTNode {
    ASTNodeType type;
    int line;
    
    union {
        // Literals
        struct { int64_t value; } integer;
        struct { float value; } float_literal;
        struct { double value; } double_literal;
        struct { char* value; } string;
        struct { bool value; } boolean;
        
        // Identifier
        struct { char* name; } identifier;
        
        // Binary operation
        struct {
            ASTNode* left;
            ASTNode* right;
            TokenType op;
        } binary;
        
        // Unary operation
        struct {
            ASTNode* operand;
            TokenType op;
        } unary;
        
        // Postfix operation (++, --)
        struct {
            ASTNode* operand;
            TokenType op;
        } postfix;
        
        // Ternary operation (? :)
        struct {
            ASTNode* condition;
            ASTNode* true_expr;
            ASTNode* false_expr;
        } ternary_op;
        
        // Sizeof operator
        struct {
            char* type_name;      // Type name if sizeof(type)
            ASTNode* expr;         // Expression if sizeof(expr)
        } sizeof_expr;
        
        // Function call
        struct {
            char* name;
            ASTNode** args;
            int arg_count;
        } call;
        
        // Variable declaration
        struct {
            char* name;
            char* type;
            ASTNode* initializer;
            bool is_const;
        } declaration;
        
        // Assignment
        struct {
            char* name;
            ASTNode* value;
        } assignment;
        
        // If statement
        struct {
            ASTNode* condition;
            ASTNode* then_branch;
            ASTNode* else_branch;
        } if_stmt;
        
        // While loop
        struct {
            ASTNode* condition;
            ASTNode* body;
        } while_stmt;
        
        // Do-while loop
        struct {
            ASTNode* body;
            ASTNode* condition;
        } do_while_stmt;
        
        // For loop
        struct {
            ASTNode* init;
            ASTNode* condition;
            ASTNode* increment;
            ASTNode* body;
        } for_stmt;
        
        // Switch statement
        struct {
            ASTNode* expression;
            ASTNode* body;  // Block containing case/default statements
        } switch_stmt;
        
        // Case statement
        struct {
            int64_t value;
            ASTNode* body;
        } case_stmt;
        
        // Default statement
        struct {
            ASTNode* body;
        } default_stmt;
        
        // Goto statement
        struct {
            char* label;
        } goto_stmt;
        
        // Label statement
        struct {
            char* name;
            ASTNode* statement;
        } label_stmt;
        
        // Return statement
        struct {
            ASTNode* value;
        } return_stmt;
        
        // Function
        struct {
            char* name;
            char** param_names;
            char** param_types;
            int param_count;
            char* return_type;
            ASTNode* body;
        } function;
        
        // Block
        struct {
            ASTNode** statements;
            int statement_count;
            int capacity;
        } block;
        
        // Program
        struct {
            ASTNode** enums;         // Top-level enum declarations
            int enum_count;
            int enum_capacity;
            ASTNode** functions;
            int function_count;
            int capacity;
        } program;
        
        // Expression statement
        struct {
            ASTNode* expression;
        } expr_stmt;
        
        // Enum declaration
        struct {
            char* name;              // enum name (optional)
            char** value_names;      // names of enum values
            int64_t* values;         // explicit values (or auto-generated)
            int value_count;
        } enum_decl;
        
        // Struct declaration
        struct {
            char* name;              // struct name
            char** field_names;      // names of fields
            int field_count;
        } struct_decl;
        
        // Member access (struct.field)
        struct {
            ASTNode* object;         // the struct variable
            char* member;            // the field name
        } member_access;
    };
};

// Parser structure
typedef struct {
    Lexer* lexer;
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
} Parser;

// Symbol table entry
typedef struct {
    char* name;
    int reg;
    int scope_depth;
    bool is_const;           // true if this is a compile-time constant (e.g., enum value)
    int64_t const_value;     // value if is_const is true
    char* type;              // variable type: "int", "float", "double", "bool", "char", etc.
} Symbol;

// Symbol table
typedef struct {
    Symbol* symbols;
    int count;
    int capacity;
    int scope_depth;
} SymbolTable;

// Code generator
typedef struct {
    FILE* output;
    SymbolTable symtab;
    int label_count;
    int loop_start;
    int loop_end;
    char** strings;
    int string_count;
    int string_capacity;
    bool reg_in_use[32];
} CodeGen;

// Function prototypes

// Lexer functions
void lexer_init(Lexer* lexer, const char* source);
Token lexer_scan_token(Lexer* lexer);

// Parser functions
void parser_init(Parser* parser, Lexer* lexer);
ASTNode* parse(Parser* parser);
void parser_error_at(Parser* parser, Token* token, const char* message);

// AST functions
ASTNode* ast_create_node(ASTNodeType type, int line);
void ast_free(ASTNode* node);

// Code generator functions
void codegen_init(CodeGen* gen, FILE* output);
void generate(CodeGen* gen, ASTNode* program);
void codegen_free(CodeGen* gen);

// Symbol table functions
void symtab_init(SymbolTable* table);
void symtab_add(SymbolTable* table, const char* name, int reg, const char* type);
void symtab_add_const(SymbolTable* table, const char* name, int64_t value);
int symtab_lookup(SymbolTable* table, const char* name);
Symbol* symtab_find(SymbolTable* table, const char* name);
void symtab_free(SymbolTable* table);
void symtab_enter_scope(SymbolTable* table);
void symtab_exit_scope(SymbolTable* table);

// Utility functions
char* string_copy(const char* str, int length);
void error(int line, const char* message);

#endif // ALGO_COMPILER_H
