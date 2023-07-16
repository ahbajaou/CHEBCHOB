#include "minishell.h"

t_cmd* create_command(char *name) 
{
    t_cmd *command = malloc(sizeof(t_cmd));
    command->name = strdup(name);
    command->args = malloc(sizeof(char*));
    command->arg_count = 0;
    command->redirection = REDIR_NONE;
    command->redirection_file = NULL;
    command->next = NULL;
    return command;
}

// void add_argument(t_cmd *command, char *arg) 
// {
//     command->args[command->arg_count] = strdup(arg);
//     command->arg_count++;
//     command->args = realloc(command->args, (command->arg_count + 1) * sizeof(char*)); // forbiden 
// }
void add_argument(t_cmd *command, char *arg) 
{
    char **new_args = malloc((command->arg_count + 2) * sizeof(char*));
    int i = 0;
    while (i < command->arg_count) 
        new_args[i] = command->args[i];
        i++;
    new_args[command->arg_count] = strdup(arg);
    new_args[command->arg_count + 1] = NULL; 
    free(command->args);
    command->args = new_args;
    command->arg_count++;
}

void set_redirection(t_cmd *command, char *filename, t_redirection redirection) 
{
    command->redirection = redirection;
    command->redirection_file = strdup(filename);
}

void handle_pipe(char **token, char **lasts, t_cmd **current) 
{
    *token = custom(NULL, " ", lasts);
    (*current)->next = create_command(*token);
    *current = (*current)->next;
}

void handle_redirection(char **token, char **lasts, t_cmd *current) 
{
    char *redirection = *token;
    *token = custom(NULL, " ", lasts);
    if (*token && (*token[0] == '>' || *token[0] == '<'))
    {
        strcat(redirection, *token); // Combine the tokens
        *token = custom(NULL, " ", lasts);
    }
    if (strcmp(redirection, ">") == 0)
        set_redirection(current, *token, REDIR_OUTPUT);
    else if (strcmp(redirection, "<") == 0)
        set_redirection(current, *token, REDIR_INPUT);
    else if (strcmp(redirection, ">>") == 0)
        set_redirection(current, *token, REDIR_APPEND);
    else if (strcmp(redirection, "<<") == 0)
        set_redirection(current, *token, REDIR_HEREDOC);
}

void print_commands(t_cmd *head) 
{
    t_cmd *current = head;
    while (current != NULL) 
    {
        int i = 0;
        printf("Command: %s\n", current->name);
        while (i < current->arg_count) 
        {
            printf("Argument: %s\n", current->args[i]);
            i++;
        }
        if (current->redirection != REDIR_NONE)
        {
            printf("Redirection: ");
            if (current->redirection == REDIR_INPUT)
                printf("< ");
            else if (current->redirection == REDIR_OUTPUT)
                printf("> ");
            else if (current->redirection == REDIR_APPEND)
                printf(">> ");
            else if (current->redirection == REDIR_HEREDOC)
                printf("<< ");   
            printf("%s\n", current->redirection_file);
        }
        current = current->next;
    }
}

// const char* get_redirection_type(t_redirection redirection) 
// {
//     switch(redirection) 
//     {
//         case REDIR_NONE:
//             return "REDIR_NONE";
//         case REDIR_INPUT:
//             return "REDIR_INPUT";
//         case REDIR_OUTPUT:
//             return "REDIR_OUTPUT";
//         case REDIR_APPEND:
//             return "REDIR_APPEND";
//         case REDIR_HEREDOC:
//             return "REDIR_HEREDOC";
//         default:
//             return "UNKNOWN";
//     }
// }

// void print_commands(t_cmd *head) 
// {
//     t_cmd *current = head;
//     while (current != NULL) 
//     {
//         printf("Command: %s\n", current->name);
//         int i = 0;
//         while(i < current->arg_count) 
//         {
//             printf("Argument: %s\n", current->args[i]);
//             i++;
//         }
//         if (current->redirection != REDIR_NONE)
//         {
//             printf("Redirection Type: %s\n", get_redirection_type(current->redirection));
//             printf("Redirection File: %s\n", current->redirection_file);
//         }
//         current = current->next;
//     }
// }


t_cmd* parse_input(char *input) 
{
    char *token, *lasts;
    token = custom(input, " ", &lasts);
    t_cmd *head = NULL, *current = NULL;
    while (token != NULL) 
    {
        if (strcmp(token, "|") == 0) 
            handle_pipe(&token, &lasts, &current);
        else if (token[0] == '>' || token[0] == '<') 
            handle_redirection(&token, &lasts, current);
        else 
        {
            if (head == NULL) 
            {
                head = create_command(token);
                current = head;
            } else 
            {
                add_argument(current, token);
            }
        }
        token = custom(NULL, " ", &lasts);
    }
    return head;
}