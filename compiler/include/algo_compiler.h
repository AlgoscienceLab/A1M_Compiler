#ifndef ALGO_COMPILER_H
#define ALGO_COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Token types
typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_ARROW
} TokenType;

// Keywords
typedef enum {
    KW_FUNC,
    KW_RETURN,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_FOR,
    KW_LET,
    KW_CONST,
    KW_INT,
    KW_BOOL,
    KW_VOID,
    KW_TRUE,
    KW_FALSE,
    KW_BREAK,
    KW_CONTINUE,
    KW_PRINT
} Keyword;

// Token structure
typedef struct {
    TokenType type;
    char *value;
    int line;
    int column;
} Token;

// AST node types
typedef enum {
    AST_PROGRAM,
    AST_FUNCTION,
    AST_BLOCK,
    AST_VAR_DECL,
    AST_ASSIGNMENT,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_FOR_STMT,
    AST_RETURN_STMT,
    AST_EXPR_STMT,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_CALL,
    AST_IDENTIFIER,
    AST_NUMBER,
    AST_STRING
} ASTNodeType;

// AST node
typedef struct ASTNode {
    ASTNodeType type;
    char *value;
    struct ASTNode **children;
    int child_count;
    int line;
} ASTNode;

// Compiler context
typedef struct {
    Token *tokens;
    int token_count;
    int current_token;
    FILE *output;
    int label_counter;
    int register_counter;
} Compiler;

// Function prototypes
Token* tokenize(const char *source, int *token_count);
ASTNode* parse(Token *tokens, int token_count);
void generate_code(Compiler *compiler, ASTNode *ast);
void compile_file(const char *input_file, const char *output_file);

// Helper functions
void free_tokens(Token *tokens, int count);
void free_ast(ASTNode *node);
char* read_file(const char *filename);

#endif // ALGO_COMPILER_H
