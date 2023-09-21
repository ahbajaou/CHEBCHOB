#include "minishell.h"

char** lexer(char* input) 
{
    int size = 64; // par default 
    char** tokens = malloc(size * sizeof(char*));
    if (!tokens) 
        exit(1);
    char* token = custom_str(input, " ");
    int i = 0;
    while (token != NULL) 
    {
        if (i >= size) 
        {
            size *= 2; // si le tableau est plein je double la allocation
            tokens = realloc(tokens, size * sizeof(char*)); // realloc forbiden je le change apres 
            if (!tokens) 
                exit(1);
        }
        tokens[i] = malloc((strlen(token) + 1) * sizeof(char));
        if (!tokens[i]) 
            exit(1);
        strcpy(tokens[i], token);
        i++;
        token = custom_str(NULL, " ");
    }
    tokens[i] = NULL;
    return tokens;
}
void free_tokens(char** tokens) 
{
    int i = 0;
    while (tokens[i] != NULL) 
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}
