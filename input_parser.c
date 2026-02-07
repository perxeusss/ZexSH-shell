#include "zexsh.h"

char** parse_input(char* input) {

    size_t buffer_size = MAX ;

    char** tokens = malloc(buffer_size * sizeof(char*)) ;
    if(!tokens) {
        perror("No tokens") ;
        exit(EXIT_FAILURE) ;
    }

    size_t position = 0;
    size_t i = 0;

    while (input[i]) {
        /* skip spaces */
        while (input[i] == ' ')
            i++;
        if (!input[i])
            break;

        char *token = &input[i];
        size_t token_length = 0;

        while (input[i] && input[i] != ' ') {
            token_length++;
            i++;
        }

        tokens[position] = malloc(token_length + 1); /* +1 for '\0' */
        if(!tokens[position]) {
            perror("No tokens") ;
            exit(EXIT_FAILURE) ;
        }

        for (size_t j = 0; j < token_length; j++) {
            tokens[position][j] = token[j];
        }
        tokens[position][token_length] = '\0'; /* correct null-termination */
        position++;
    }

    tokens[position] = NULL ;
    return tokens ;
}

void free_tokens(char** tokens) {
    if(!tokens) return ;

    for(size_t i = 0 ; tokens[i] ; i++) {
        free(tokens[i]) ;
    }
    free(tokens) ;
}
