#include "minishell.h"

char** lexer(char* input) 
{
    int size = 64;
    char** tokens = malloc(size * sizeof(char*));
    if (!tokens) 
        exit(1);

    char* token;
    int i = 0;
    while (*input) 
    {
        while (isspace(*input)) 
            input++;
        if (*input == '"' || *input == '\'') 
        {
            char quote = *input++;
            char* start = input;
            while (*input && *input != quote) 
                input++;
            token = strndup(start, input - start);
            if (*input) 
                input++;
        } 
        else 
        {
            char* start = input;
            while (*input && !isspace(*input) && *input != '"' && *input != '=') 
                input++;
            if (*input == '=')
            {
                input++;
                if (*input == '"' || *input == '\'')
                {
                    char quote = *input++;
                    while (*input && *input != quote) 
                        input++;
                    if (*input) 
                        input++;
                }
                else
                {
                    while (*input && !isspace(*input) && *input != '"') 
                        input++;
                }
            }
            token = strndup(start, input - start);
        }
        // printf("Token lexer: %s\n", token);  // Ajouté
        if (i >= size) 
        {
            size *= 2; // si le tableau est plein je double la allocation
            tokens = realloc(tokens, size * sizeof(char*)); 
            if (!tokens) 
                exit(1);
        }
        tokens[i++] = token;
    }
    tokens[i] = NULL;
    return tokens;
}

void free_tokens(char** tokens) 
{
    int i = 0;
    while (tokens[i] != NULL) 
    {
        // free(tokens[i]);
        tokens[i] = NULL;
        i++;
    }
    free(tokens);
}
