#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/compiler.h"

static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'\n", path);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    char* buffer = malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate memory\n");
        fclose(file);
        return NULL;
    }
    
    size_t bytes_read = fread(buffer, 1, size, file);
    buffer[bytes_read] = '\0';
    
    fclose(file);
    return buffer;
}

// Simple preprocessor to handle #include directives
static char* preprocess(const char* source, const char* base_dir) {
    // Start with 2x source size, grow dynamically if needed
    size_t capacity = strlen(source) * 2;
    size_t used = 0;
    char* result = malloc(capacity);
    if (!result) {
        fprintf(stderr, "Error: Could not allocate memory for preprocessing\n");
        return NULL;
    }
    
    const char* src = source;
    
    while (*src) {
        // Check for #include directive
        if (*src == '#') {
            const char* line_start = src;
            src++; // skip #
            
            // Skip whitespace
            while (*src == ' ' || *src == '\t') src++;
            
            // Check if it's "include"
            if (strncmp(src, "include", 7) == 0) {
                src += 7;
                
                // Skip whitespace
                while (*src == ' ' || *src == '\t') src++;
                
                // Expect "filename"
                if (*src == '"') {
                    src++; // skip opening "
                    const char* filename_start = src;
                    
                    // Find closing "
                    while (*src && *src != '"' && *src != '\n') src++;
                    
                    if (*src == '"') {
                        int filename_len = (int)(src - filename_start);
                        char filename[256];
                        
                        // Build full path (base_dir + filename)
                        if (base_dir && base_dir[0]) {
                            snprintf(filename, sizeof(filename), "%s/%.*s", 
                                    base_dir, filename_len, filename_start);
                        } else {
                            snprintf(filename, sizeof(filename), "%.*s", 
                                    filename_len, filename_start);
                        }
                        
                        // Read included file
                        char* included = read_file(filename);
                        if (included) {
                            size_t included_len = strlen(included);
                            
                            // Ensure we have enough space (grow if needed)
                            while (used + included_len + 2 >= capacity) {
                                capacity *= 2;
                                char* new_result = realloc(result, capacity);
                                if (!new_result) {
                                    fprintf(stderr, "Error: Could not expand preprocessor buffer\n");
                                    free(result);
                                    free(included);
                                    return NULL;
                                }
                                result = new_result;
                            }
                            
                            // Copy included content
                            memcpy(result + used, included, included_len);
                            used += included_len;
                            result[used++] = '\n'; // Add newline after included content
                            
                            free(included);
                        } else {
                            fprintf(stderr, "Warning: Could not include file '%s'\n", filename);
                        }
                        
                        src++; // skip closing "
                        
                        // Skip to end of line
                        while (*src && *src != '\n') src++;
                        if (*src == '\n') src++;
                        continue;
                    }
                }
            }
            
            // If we get here, it wasn't a valid include, copy the line as-is
            src = line_start;
        }
        
        // Ensure space for one more character
        if (used + 1 >= capacity) {
            capacity *= 2;
            char* new_result = realloc(result, capacity);
            if (!new_result) {
                fprintf(stderr, "Error: Could not expand preprocessor buffer\n");
                free(result);
                return NULL;
            }
            result = new_result;
        }
        
        // Copy character
        result[used++] = *src++;
    }
    
    result[used] = '\0';
    
    // Shrink to actual size to save memory
    char* final_result = realloc(result, used + 1);
    if (final_result) {
        return final_result;
    }
    return result;  // Return original if realloc fails (still valid)
}

// Extract directory from file path
static void get_directory(const char* path, char* dir, size_t dir_size) {
    const char* last_slash = strrchr(path, '/');
    if (last_slash) {
        size_t len = last_slash - path;
        if (len >= dir_size) len = dir_size - 1;
        strncpy(dir, path, len);
        dir[len] = '\0';
    } else {
        dir[0] = '\0';  // No directory, use current
    }
}

static void print_usage(const char* program) {
    fprintf(stderr, "Usage: %s <input.algo> [-o <output.asm>]\n", program);
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -o <file>    Output assembly file (default: <input>.asm)\n");
    fprintf(stderr, "  -h, --help   Show this help message\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    const char* input_file = NULL;
    const char* output_file = NULL;
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -o requires an argument\n");
                return 1;
            }
            output_file = argv[++i];
        } else if (!input_file) {
            input_file = argv[i];
        } else {
            fprintf(stderr, "Error: Unexpected argument '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }
    
    if (!input_file) {
        fprintf(stderr, "Error: No input file specified\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Generate default output filename if not specified
    char default_output[256];
    if (!output_file) {
        const char* dot = strrchr(input_file, '.');
        if (dot && strcmp(dot, ".algo") == 0) {
            size_t base_len = dot - input_file;
            snprintf(default_output, sizeof(default_output), "%.*s.asm", (int)base_len, input_file);
        } else {
            snprintf(default_output, sizeof(default_output), "%s.asm", input_file);
        }
        output_file = default_output;
    }
    
    // Read source file
    char* source = read_file(input_file);
    if (!source) {
        return 1;
    }
    
    // Get directory for relative includes
    char base_dir[256];
    get_directory(input_file, base_dir, sizeof(base_dir));
    
    // Preprocess (handle includes)
    char* preprocessed = preprocess(source, base_dir);
    free(source);  // Free original source
    
    if (!preprocessed) {
        return 1;
    }
    
    printf("Compiling %s...\n", input_file);
    
    // Initialize lexer with preprocessed source
    Lexer lexer;
    lexer_init(&lexer, preprocessed);
    
    // Initialize parser
    Parser parser;
    parser_init(&parser, &lexer);
    
    // Parse source code
    ASTNode* program = parse(&parser);
    
    if (parser.had_error) {
        fprintf(stderr, "Compilation failed due to parse errors\n");
        ast_free(program);
        free(preprocessed);
        return 1;
    }
    
    // Open output file
    FILE* output = fopen(output_file, "w");
    if (!output) {
        fprintf(stderr, "Error: Could not open output file '%s'\n", output_file);
        ast_free(program);
        free(preprocessed);
        return 1;
    }
    
    // Initialize code generator
    CodeGen codegen;
    codegen_init(&codegen, output);
    
    // Generate assembly code
    generate(&codegen, program);
    
    // Cleanup
    codegen_free(&codegen);
    fclose(output);
    ast_free(program);
    free(preprocessed);
    
    printf("Successfully generated %s\n", output_file);
    
    return 0;
}
