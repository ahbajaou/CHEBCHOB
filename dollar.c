#include "minishell.h"

size_t calculate_required_length(const char* input) 
{
    size_t total_length = 0;
    while (*input) 
    {
        if (*input == '$') 
        {
            input++;
            char var_name[256];
            char* var_start = var_name;
            while (*input && (isalnum(*input) || *input == '_')) 
                *var_start++ = *input++;
            *var_start = '\0';
            char* var_value = getenv(var_name);
            if (var_value)
                total_length += strlen(var_value);
        } 
        else 
        {
            total_length++;
            input++;
        }
    }
    return total_length;
}

int check_quotes(const char* input) 
{
    char quote_char = '\0';
    while (*input) 
    {
        if (*input == '\'' && quote_char != '"') 
        {
            if (quote_char == '\'') 
                quote_char = '\0';
            else 
                quote_char = '\'';
            input++;
        } 
        else if (*input == '"' && quote_char != '\'') 
        {
            if (quote_char == '"') 
                quote_char = '\0';
            else 
                quote_char = '"';
            input++;
        } 
        else 
            input++;
    }
    return (quote_char == '\0');  // Retourne 1 si tous les guillemets sont correctement fermés, 0 sinon
}

char* read_input_with_quotes() 
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char* full_input = malloc(1);
    full_input[0] = '\0';
    size_t full_len = 0;

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        full_input = realloc(full_input, full_len + read + 1);
        strcat(full_input, line);
        full_len += read;

        if (full_input[full_len - 1] == '\n') 
        {
            full_input[full_len - 1] = '\0';
            if (check_quotes(full_input)) 
                break;
            else 
                printf("> ");
        }
    }
    free(line);
    return full_input;
}

char* replace_env_vars(const char* input) 
{
    char* result = NULL;
    char* buffer = malloc(calculate_required_length(input) + 1);
    if (!buffer) exit(1);
    const char* p = input;
    char* q = buffer;
    while (*p) 
    {
        if (*p == '$') 
        {
            const char* start = p + 1;
            while (isalnum(*start) || *start == '_') start++;
            char varname[256];
            strncpy(varname, p + 1, start - p - 1);
            varname[start - p - 1] = '\0';
            char* value = getenv(varname);
            if (value) 
            {
                strcpy(q, value);
                q += strlen(value);
            }
            p = start;
        } 
        else 
            *q++ = *p++;
    }
    *q = '\0';
    result = strdup(buffer);
    free(buffer);
    return result;
}
