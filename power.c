#include "minishell.h"

t_cmd* create_command(char *name) 
{
    t_cmd *command = calloc(1, sizeof(t_cmd));
    if (!command) 
    {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(1);
    }
    if (name != NULL)
    {
        command->name = strdup(name);
        if (!command->name) 
        {
            fprintf(stderr, "Erreur d'allocation de mémoire.\n");
            free(command);
            exit(1);
        }
    }
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
    add_redirection(command, filename, redirection);
}

// void set_redirection(t_cmd *command, char *filename, t_redirection redirection) 
// {
//     if (!command)
//     {
//         fprintf(stderr, "Erreur : la commande est NULL.\n");
//         return;
//     }
//     command->redirection = redirection;
//     if (filename) 
//         command->redirection_file = strdup(filename);
//     else 
//         command->redirection_file = NULL;
// }

void add_redirection(t_cmd *command, char *filename, t_redirection redirection) 
{
    t_redirection_list *new_redir = calloc(1, sizeof(t_redirection_list));
    new_redir->redirection_type = redirection;
    new_redir->filename = strdup(filename);
    new_redir->next = NULL;

    if (!command->redirections) 
        command->redirections = new_redir;
    else 
    {
        t_redirection_list *temp = command->redirections;
        while (temp->next) temp = temp->next;
        temp->next = new_redir;
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
    if (!*token) 
    {
        error(REDIR_ERROR);
        return;
    }
    if (strcmp(redirection, ">") == 0)
        add_redirection(current, *token, REDIR_OUTPUT);
    else if (strcmp(redirection, "<") == 0)
        add_redirection(current, *token, REDIR_INPUT);
    else if (strcmp(redirection, ">>") == 0)
        add_redirection(current, *token, REDIR_APPEND);
    else if (strcmp(redirection, "<<") == 0)
        add_redirection(current, *token, REDIR_HEREDOC);

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
        if (current->redirections) 
        {
        t_redirection_list *temp = current->redirections;
        while (temp) 
        {
        printf("Redirection: ");
        if (temp->redirection_type == REDIR_INPUT)
            printf("< ");
        else if (temp->redirection_type == REDIR_OUTPUT)
            printf("> ");
        else if (temp->redirection_type == REDIR_APPEND)
            printf(">> ");
        else if (temp->redirection_type == REDIR_HEREDOC)
            printf("<< ");   
        printf("%s\n", temp->filename);
        temp = temp->next;
        }
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
    if (!input || strlen(input) == 0) 
        return NULL;
    char *token, *lasts;
    token = custom(input, " ", &lasts);
    if (!token) 
    {
        return NULL;
    }
    t_cmd *head = NULL, *current = NULL;
    while (token != NULL) 
    {
         if (!token || strlen(token) == 0 || strspn(token, " \t\n\r") == strlen(token)) 
        {
            token = custom(NULL, " ", &lasts);
            continue;
        }
        if (!current) 
        {
            current = create_command(NULL);
            if (!head)
                head = current;
        }
        if (token && strcmp(token, "|") == 0)  
            handle_pipe(&token, &lasts, &current);
        else if (token &&(token[0] == '>' || token[0] == '<')) 
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

void free_redirection_list(t_redirection_list *head) 
{
    while (head) 
    {
        t_redirection_list *temp = head;
        head = head->next;
        if (temp->filename) free(temp->filename);
        free(temp);
    }
}

void free_cmd(t_cmd *cmd) 
{
    if (cmd->name)
    { 
        free(cmd->name);
        cmd->name =NULL;
    }
    for (int i = 0; i < cmd->arg_count; i++) 
        if (cmd->args[i]) free(cmd->args[i]);
    free(cmd->args);
    if (cmd->redirection_file) free(cmd->redirection_file);
    free(cmd);
}
void free_command(t_cmd* command) 
{
    if (!command) 
        return;

    if (command->name)
        free(command->name);

    if (command->args) 
    {
        for (int i = 0; i < command->arg_count; i++) 
        {
            if (command->args[i])
                free(command->args[i]);
        }
        free(command->args);
    }

    if (command->redirection_file)
        free(command->redirection_file);

    if (command->redirections)
        free_redirection_list(command->redirections);

    free(command);
}


