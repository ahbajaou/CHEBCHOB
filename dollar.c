#include "minishell.h"

size_t calculate_required_length(const char* input) 
{
    size_t total_length = 0;
    while (*input) 
    {
        if (*input == '$') 
        {
            input++;
            const char *start = input;
            while (*input && (isalnum(*input) || *input == '_')) 
                input++;

            size_t var_name_length = input - start;
            char* var_name = malloc(var_name_length + 1);
            if (!var_name) 
            {
                perror("malloc");
                exit(1);
            }
            strncpy(var_name, start, var_name_length);
            var_name[var_name_length] = '\0'; 
            
            char* var_value = getenv(var_name);
            if (var_value)
                total_length += strlen(var_value);
            
            free(var_name);
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
    int is_escaped = 0;

    while (*input) 
    {
        if (*input == '\\' && (input[1] == '"' || input[1] == '\'')) 
        {
            is_escaped = 1;
            input += 2;
            continue;
        }
        if (!is_escaped && *input == '\'' && quote_char != '"') 
        {
            if (quote_char == '\'') 
                quote_char = '\0';
            else 
                quote_char = '\'';
        } 
        else if (!is_escaped && *input == '"' && quote_char != '\'') 
        {
            if (quote_char == '"') 
                quote_char = '\0';
            else 
                quote_char = '"';
        } 
        is_escaped = 0;
        input++;
    }

    return (quote_char == '\0'); 
}

char* read_input_with_quotes() 
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    char* full_input = malloc(1);
    full_input[0] = '\0';
    size_t full_len = 0;
    char quote_char = '\0';
    int is_escaped = 0;

    while ((read = getline(&line, &len, stdin)) != -1)
    {
        full_input = realloc(full_input, full_len + read + 1);
        strcat(full_input, line);
        full_len += read;

        if (full_input[full_len - 1] == '\n') 
            full_input[full_len - 1] = '\0';
        for(size_t i = 0; full_input[i] != '\0'; i++)
        {
            if(full_input[i] == '\\' && !is_escaped && (quote_char == '\"' || quote_char == '\0'))
            {
                is_escaped = 1;
                continue;
            }

            if((full_input[i] == '"' || full_input[i] == '\'') && !is_escaped)
            {
                if(quote_char == full_input[i])
                    quote_char = '\0';
                else if(quote_char == '\0')
                    quote_char = full_input[i];
            }

            if(is_escaped)
                is_escaped = 0;
        }

        if (quote_char == '\0' && !is_escaped) 
            break;
        else 
            printf("> ");
    }

    free(line);
    return full_input;
}


// char* read_input_with_quotes() 
// {
//     char* line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     char* full_input = malloc(1);
//     full_input[0] = '\0';
//     size_t full_len = 0;

//     while ((read = getline(&line, &len, stdin)) != -1)
//     {
//         full_input = realloc(full_input, full_len + read + 1);
//         strcat(full_input, line);
//         full_len += read;

//         if (full_input[full_len - 1] == '\n') 
//         {
//             full_input[full_len - 1] = '\0';  // Remove newline
//             if (check_quotes(full_input)) 
//                 break;
//             else 
//                 printf("> ");  // Prompt for continuation of input
//         }
//     }
//     free(line);
//     return full_input;
// }


char* replace_env_vars(const char* input) 
{
    size_t required_length = calculate_required_length(input);
    char* result = malloc(required_length + 1);
    if (!result) 
    {
        perror("malloc");
        exit(1);
    }

    char* current = result;
    char quote_char = '\0';
    int is_escaped = 0;

    while (*input) 
    {
        if (*input == '\\' && quote_char == '"' && 
           (input[1] == '"' || input[1] == '\\' || input[1] == '$'))
        {
            *current++ = input[1];
            input += 2;
            continue;
        }
        // Quote handling
        if (*input == '"' && quote_char != '\'') 
        {
            if (!is_escaped && quote_char == '"') 
                quote_char = '\0';
            else if (!is_escaped) 
                quote_char = '"';
            input++;
            continue;
        }
        if (*input == '\'' && quote_char != '"') 
        {
            if (quote_char == '\'') 
                quote_char = '\0';
            else 
                quote_char = '\'';
            input++;
            continue;
        }
        // Environment variable
        if (*input == '$' && quote_char != '\'') 
        {
            input++;
            char var_name[256];
            char* var_start = var_name;
            while (*input && (isalnum(*input) || *input == '_')) 
                *var_start++ = *input++;
            *var_start = '\0';
            char* var_value = getenv(var_name);
            if (var_value) 
            {
                strncpy(current, var_value, required_length - (current - result));
                current += strlen(var_value);
            }
            continue;
        }
        if (*input != '\\') 
            is_escaped = 0;
        *current++ = *input++;
    }
    *current = '\0';
    return result;
}