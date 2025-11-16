#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/compiler.h"

void lexer_init(Lexer* lexer, const char* source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
}

static bool is_at_end(Lexer* lexer) {
    return *lexer->current == '\0';
}

static char advance(Lexer* lexer) {
    lexer->current++;
    return lexer->current[-1];
}

static char peek(Lexer* lexer) {
    return *lexer->current;
}

static char peek_next(Lexer* lexer) {
    if (is_at_end(lexer)) return '\0';
    return lexer->current[1];
}

static bool match(Lexer* lexer, char expected) {
    if (is_at_end(lexer)) return false;
    if (*lexer->current != expected) return false;
    lexer->current++;
    return true;
}

static Token make_token(Lexer* lexer, TokenType type) {
    Token token;
    token.type = type;
    token.start = lexer->start;
    token.length = (int)(lexer->current - lexer->start);
    token.line = lexer->line;
    return token;
}

static Token error_token(Lexer* lexer, const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = lexer->line;
    return token;
}

static void skip_whitespace(Lexer* lexer) {
    for (;;) {
        char c = peek(lexer);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(lexer);
                break;
            case '\n':
                lexer->line++;
                advance(lexer);
                break;
            case '/':
                if (peek_next(lexer) == '/') {
                    // Single-line comment
                    while (peek(lexer) != '\n' && !is_at_end(lexer)) {
                        advance(lexer);
                    }
                } else if (peek_next(lexer) == '*') {
                    // Multi-line comment
                    advance(lexer); // '/'
                    advance(lexer); // '*'
                    while (!is_at_end(lexer)) {
                        if (peek(lexer) == '*' && peek_next(lexer) == '/') {
                            advance(lexer); // '*'
                            advance(lexer); // '/'
                            break;
                        }
                        if (peek(lexer) == '\n') lexer->line++;
                        advance(lexer);
                    }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

static TokenType check_keyword(Lexer* lexer, int start, int length,
                               const char* rest, TokenType type) {
    if (lexer->current - lexer->start == start + length &&
        memcmp(lexer->start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type(Lexer* lexer) {
    switch (lexer->start[0]) {
        case 'a':
            if (lexer->current - lexer->start > 1) {
                if (lexer->start[1] == 'u') return check_keyword(lexer, 2, 2, "to", TOKEN_AUTO);
            }
            break;
        case 'b':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'o': return check_keyword(lexer, 2, 2, "ol", TOKEN_BOOL);
                    case 'r': return check_keyword(lexer, 2, 3, "eak", TOKEN_BREAK);
                }
            }
            break;
        case 'c':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'a': return check_keyword(lexer, 2, 2, "se", TOKEN_CASE);
                    case 'h': return check_keyword(lexer, 2, 2, "ar", TOKEN_CHAR);
                    case 'o':
                        if (lexer->current - lexer->start > 4) {
                            switch (lexer->start[4]) {
                                case 't': return check_keyword(lexer, 2, 3, "nst", TOKEN_CONST);
                                case 'i': return check_keyword(lexer, 2, 6, "ntinue", TOKEN_CONTINUE);
                            }
                        }
                        break;
                }
            }
            break;
        case 'd':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'o': return check_keyword(lexer, 2, 0, "", TOKEN_DO);
                    case 'e': return check_keyword(lexer, 2, 5, "fault", TOKEN_DEFAULT);
                    case 'u': return check_keyword(lexer, 2, 4, "uble", TOKEN_DOUBLE);
                }
            }
            break;
        case 'e':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'l': return check_keyword(lexer, 2, 2, "se", TOKEN_ELSE);
                    case 'n': return check_keyword(lexer, 2, 2, "um", TOKEN_ENUM);
                    case 'x': return check_keyword(lexer, 2, 4, "tern", TOKEN_EXTERN);
                }
            }
            break;
        case 'f':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'a': return check_keyword(lexer, 2, 3, "lse", TOKEN_FALSE);
                    case 'l': return check_keyword(lexer, 2, 3, "oat", TOKEN_FLOAT);
                    case 'o': return check_keyword(lexer, 2, 1, "r", TOKEN_FOR);
                    case 'u': return check_keyword(lexer, 2, 2, "nc", TOKEN_FUNC);
                }
            }
            break;
        case 'g': return check_keyword(lexer, 1, 3, "oto", TOKEN_GOTO);
        case 'i':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'f': return check_keyword(lexer, 2, 0, "", TOKEN_IF);
                    case 'n': return check_keyword(lexer, 2, 1, "t", TOKEN_INT);
                }
            }
            break;
        case 'l':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'e': return check_keyword(lexer, 2, 1, "t", TOKEN_LET);
                    case 'o': return check_keyword(lexer, 2, 2, "ng", TOKEN_LONG);
                }
            }
            break;
        case 'r':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'e':
                        if (lexer->current - lexer->start > 3) {
                            switch (lexer->start[3]) {
                                case 'u': return check_keyword(lexer, 2, 4, "turn", TOKEN_RETURN);
                                case 'i': return check_keyword(lexer, 2, 6, "gister", TOKEN_REGISTER);
                            }
                        }
                        break;
                }
            }
            break;
        case 's':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'h': return check_keyword(lexer, 2, 3, "ort", TOKEN_SHORT);
                    case 'i':
                        if (lexer->current - lexer->start > 2) {
                            switch (lexer->start[2]) {
                                case 'z': return check_keyword(lexer, 2, 4, "zeof", TOKEN_SIZEOF);
                                case 'g': return check_keyword(lexer, 2, 4, "gned", TOKEN_SIGNED);
                            }
                        }
                        break;
                    case 't':
                        if (lexer->current - lexer->start > 2) {
                            switch (lexer->start[2]) {
                                case 'a': return check_keyword(lexer, 2, 4, "atic", TOKEN_STATIC);
                                case 'r':
                                    if (lexer->current - lexer->start > 3) {
                                        if (lexer->start[3] == 'i') return check_keyword(lexer, 2, 4, "ring", TOKEN_STRING_TYPE);
                                        if (lexer->start[3] == 'u') return check_keyword(lexer, 2, 4, "ruct", TOKEN_STRUCT);
                                    }
                                    break;
                            }
                        }
                        break;
                    case 'w': return check_keyword(lexer, 2, 4, "itch", TOKEN_SWITCH);
                }
            }
            break;
        case 't':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'r': return check_keyword(lexer, 2, 2, "ue", TOKEN_TRUE);
                    case 'y': return check_keyword(lexer, 2, 5, "pedef", TOKEN_TYPEDEF);
                }
            }
            break;
        case 'u':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'n':
                        if (lexer->current - lexer->start > 3) {
                            switch (lexer->start[3]) {
                                case 'i': return check_keyword(lexer, 2, 3, "ion", TOKEN_UNION);
                                case 's': return check_keyword(lexer, 2, 6, "signed", TOKEN_UNSIGNED);
                            }
                        }
                        break;
                }
            }
            break;
        case 'v':
            if (lexer->current - lexer->start > 1) {
                switch (lexer->start[1]) {
                    case 'o':
                        if (lexer->current - lexer->start > 3) {
                            switch (lexer->start[3]) {
                                case 'd': return check_keyword(lexer, 2, 2, "id", TOKEN_VOID);
                                case 'a': return check_keyword(lexer, 2, 6, "latile", TOKEN_VOLATILE);
                            }
                        }
                        break;
                }
            }
            break;
        case 'w': return check_keyword(lexer, 1, 4, "hile", TOKEN_WHILE);
    }
    return TOKEN_IDENTIFIER;
}

static Token identifier(Lexer* lexer) {
    while (isalnum(peek(lexer)) || peek(lexer) == '_') {
        advance(lexer);
    }
    return make_token(lexer, identifier_type(lexer));
}

static Token number(Lexer* lexer) {
    bool is_float = false;
    bool is_double = false;
    
    // Parse integer part
    while (isdigit(peek(lexer))) {
        advance(lexer);
    }
    
    // Look for decimal point
    if (peek(lexer) == '.' && isdigit(peek_next(lexer))) {
        is_float = true;
        
        // Consume the '.'
        advance(lexer);
        
        // Parse fractional part
        while (isdigit(peek(lexer))) {
            advance(lexer);
        }
    }
    
    // Look for exponent (e or E)
    if (peek(lexer) == 'e' || peek(lexer) == 'E') {
        is_float = true;
        advance(lexer);
        
        // Optional sign
        if (peek(lexer) == '+' || peek(lexer) == '-') {
            advance(lexer);
        }
        
        // Exponent digits
        while (isdigit(peek(lexer))) {
            advance(lexer);
        }
    }
    
    // Check for float/double suffix
    if (peek(lexer) == 'f' || peek(lexer) == 'F') {
        advance(lexer);
        return make_token(lexer, TOKEN_FLOAT_LITERAL);
    } else if (peek(lexer) == 'd' || peek(lexer) == 'D') {
        advance(lexer);
        is_double = true;
    }
    
    // Default to double if decimal point or exponent found, otherwise int
    if (is_float || is_double) {
        return make_token(lexer, TOKEN_DOUBLE_LITERAL);
    }
    
    return make_token(lexer, TOKEN_INTEGER);
}

static Token string(Lexer* lexer) {
    while (peek(lexer) != '"' && !is_at_end(lexer)) {
        if (peek(lexer) == '\n') lexer->line++;
        // Handle escape sequences
        if (peek(lexer) == '\\') {
            advance(lexer); // Skip backslash
            if (!is_at_end(lexer)) {
                advance(lexer); // Skip escaped character
            }
        } else {
            advance(lexer);
        }
    }
    
    if (is_at_end(lexer)) {
        return error_token(lexer, "Unterminated string");
    }
    
    advance(lexer); // Closing "
    return make_token(lexer, TOKEN_STRING);
}

Token lexer_scan_token(Lexer* lexer) {
    skip_whitespace(lexer);
    
    lexer->start = lexer->current;
    
    if (is_at_end(lexer)) {
        return make_token(lexer, TOKEN_EOF);
    }
    
    char c = advance(lexer);
    
    // Handle preprocessor directives
    if (c == '#') {
        // Skip whitespace after #
        while (peek(lexer) == ' ' || peek(lexer) == '\t') {
            advance(lexer);
        }
        
        // Check for attribute directives like #[nomain]
        if (peek(lexer) == '[') {
            // Skip the entire attribute directive
            advance(lexer); // skip '['
            while (peek(lexer) != ']' && !is_at_end(lexer)) {
                if (peek(lexer) == '\n') lexer->line++;
                advance(lexer);
            }
            if (peek(lexer) == ']') {
                advance(lexer); // skip ']'
            }
            // Skip to next token
            skip_whitespace(lexer);
            return lexer_scan_token(lexer);
        }
        
        // Check for 'include'
        if (peek(lexer) == 'i') {
            const char* start = lexer->current;
            while (isalpha(peek(lexer))) {
                advance(lexer);
            }
            int len = (int)(lexer->current - start);
            if (len == 7 && strncmp(start, "include", 7) == 0) {
                return make_token(lexer, TOKEN_INCLUDE);
            }
        }
        // If not include or attribute, treat as error
        return error_token(lexer, "Unknown preprocessor directive");
    }
    
    if (isalpha(c) || c == '_') return identifier(lexer);
    if (isdigit(c)) return number(lexer);
    
    switch (c) {
        case '(': return make_token(lexer, TOKEN_LEFT_PAREN);
        case ')': return make_token(lexer, TOKEN_RIGHT_PAREN);
        case '{': return make_token(lexer, TOKEN_LEFT_BRACE);
        case '}': return make_token(lexer, TOKEN_RIGHT_BRACE);
        case '[': return make_token(lexer, TOKEN_LEFT_BRACKET);
        case ']': return make_token(lexer, TOKEN_RIGHT_BRACKET);
        case ',': return make_token(lexer, TOKEN_COMMA);
        case ';': return make_token(lexer, TOKEN_SEMICOLON);
        case ':': return make_token(lexer, TOKEN_COLON);
        case '?': return make_token(lexer, TOKEN_QUESTION);
        case '~': return make_token(lexer, TOKEN_TILDE);
        case '.': return make_token(lexer, TOKEN_DOT);
        
        case '+':
            if (match(lexer, '+')) return make_token(lexer, TOKEN_PLUS_PLUS);
            if (match(lexer, '=')) return make_token(lexer, TOKEN_PLUS_EQUAL);
            return make_token(lexer, TOKEN_PLUS);
        case '-':
            if (match(lexer, '-')) return make_token(lexer, TOKEN_MINUS_MINUS);
            if (match(lexer, '>')) return make_token(lexer, TOKEN_ARROW);
            if (match(lexer, '=')) return make_token(lexer, TOKEN_MINUS_EQUAL);
            return make_token(lexer, TOKEN_MINUS);
        case '*':
            return make_token(lexer, match(lexer, '=') ? TOKEN_STAR_EQUAL : TOKEN_STAR);
        case '/':
            return make_token(lexer, match(lexer, '=') ? TOKEN_SLASH_EQUAL : TOKEN_SLASH);
        case '%':
            return make_token(lexer, match(lexer, '=') ? TOKEN_PERCENT_EQUAL : TOKEN_PERCENT);
        case '^':
            return make_token(lexer, match(lexer, '=') ? TOKEN_CARET_EQUAL : TOKEN_CARET);
        case '!':
            return make_token(lexer, match(lexer, '=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return make_token(lexer, match(lexer, '=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            if (match(lexer, '<')) {
                return make_token(lexer, match(lexer, '=') ? TOKEN_LEFT_SHIFT_EQUAL : TOKEN_LEFT_SHIFT);
            }
            if (match(lexer, '=')) return make_token(lexer, TOKEN_LESS_EQUAL);
            return make_token(lexer, TOKEN_LESS);
        case '>':
            if (match(lexer, '>')) {
                return make_token(lexer, match(lexer, '=') ? TOKEN_RIGHT_SHIFT_EQUAL : TOKEN_RIGHT_SHIFT);
            }
            if (match(lexer, '=')) return make_token(lexer, TOKEN_GREATER_EQUAL);
            return make_token(lexer, TOKEN_GREATER);
        case '&':
            if (match(lexer, '&')) return make_token(lexer, TOKEN_AMPERSAND_AMPERSAND);
            if (match(lexer, '=')) return make_token(lexer, TOKEN_AMPERSAND_EQUAL);
            return make_token(lexer, TOKEN_AMPERSAND);
        case '|':
            if (match(lexer, '|')) return make_token(lexer, TOKEN_PIPE_PIPE);
            if (match(lexer, '=')) return make_token(lexer, TOKEN_PIPE_EQUAL);
            return make_token(lexer, TOKEN_PIPE);
        case '"': return string(lexer);
    }
    
    return error_token(lexer, "Unexpected character");
}
