#include "minishell.h"

t_cmd* create_command(char *name) 
{
    t_cmd *command = malloc(sizeof(t_cmd));
    if (name != NULL) 
        command->name = strdup(name);
    else 
        command->name = NULL;
    command->args = malloc(sizeof(char*));
    command->args[0] = NULL;
    command->arg_count = 0;
    command->redirection = REDIR_NONE;
    command->redirection_file = NULL;
    command->next = NULL;
    return command;
}

void add_argument(t_cmd *command, char *arg) 
{
    command->args = realloc(command->args, (command->arg_count + 2) * sizeof(char*));
    command->args[command->arg_count] = strdup(arg);
    command->arg_count++;
    command->args[command->arg_count] = NULL;
}

void set_redirection(t_cmd *command, char *filename, t_redirection redirection) 
{
    if (!command) {
        fprintf(stderr, "Erreur : la commande est NULL.\n");
        return;
    }
    command->redirection = redirection;
    if (filename) {
        command->redirection_file = strdup(filename);
    } else {
        command->redirection_file = NULL;
    }
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
    if (!*token) {
        fprintf(stderr, "Erreur : Redirection sans fichier cible.\n");
        return;
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

void handle_pipe(char **token, char **lasts, t_cmd **current) 
{
    *token = custom(NULL, " ", lasts);
    t_cmd *new_command = create_command(*token);
    (*current)->next = new_command;
    *current = new_command;
}

t_cmd* parse_input(char *input) 
{
    char *token, *lasts;
    token = custom(input, " ", &lasts);
    t_cmd *head = NULL, *current = NULL;

    while (token != NULL) 
    {
        if (!current) 
        {
            current = create_command(NULL);
            if (!head) 
                head = current;
        }

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
            }   
            else 
            {
                if (current->name == NULL)
                    current->name = strdup(token);
                else
                    add_argument(current, token);
            }
        }
        token = custom(NULL, " ", &lasts);
    }
    return head;
}
