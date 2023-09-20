#include "minishell.h"

void print_command_details(t_cmd *command) 
{
    if (!command) 
    {
        printf("Commande est NULL.\n");
        return;
    }

    printf("Commande: %s\n", command->name ? command->name : "NULL");

    printf("Arguments: ");
    for (int i = 0; i < command->arg_count; i++) 
    {
        printf("%s ", command->args[i]);
    }
    printf("\n");

    if (command->redirection != REDIR_NONE)
    {
        printf("Redirection: ");
        switch (command->redirection)
        {
            case REDIR_INPUT: printf("< "); break;
            case REDIR_OUTPUT: printf("> "); break;
            case REDIR_APPEND: printf(">> "); break;
            case REDIR_HEREDOC: printf("<< "); break;
            default: printf("NONE "); break;
        }
        printf("%s\n", command->redirection_file ? command->redirection_file : "NULL");
    }

    printf("Dup Number: %d\n", command->dup_number);
    // printf("Redirection Command: %s\n", command->redirection_cmd ? command->redirection_cmd : "NULL");

    // printf("Redirection Arguments: ");
    for (int i = 0; i < command->redirection_arg_count; i++) 
    {
        printf("%s ", command->redirection_args[i]);
    }
    printf("\n");
}

void print_all_commands(t_cmd *head) 
{
    t_cmd *current = head;
    while (current != NULL)
    {
        print_command_details(current);
        printf("-------------------------------\n"); // Pour séparer les commandes
        current = current->next;
    }
}

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
    command->dup_number = -1;
    command->redirection_cmd = NULL;
    command->redirection_args = NULL;
    command->redirection_arg_count = 0;
    command->redirection = REDIR_NONE;
    command->redirection_file = NULL;
    command->next = NULL;
    return command;
}
void add_redirection_argument(t_cmd *command, char *arg) 
{
    if (!command->redirection_args) 
    {
        command->redirection_args = malloc(sizeof(char*));
        command->redirection_args[0] = NULL;
        command->redirection_arg_count = 0;
    }
    command->redirection_args = realloc(command->redirection_args, (command->redirection_arg_count + 2) * sizeof(char*));
    command->redirection_args[command->redirection_arg_count] = strdup(arg);
    command->redirection_arg_count++;
    command->redirection_args[command->redirection_arg_count] = NULL;
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
    if (!command) 
    {
        fprintf(stderr, "Erreur : la commande est NULL.\n");
        return;
    }
    command->redirection = redirection;
    if (filename) 
        command->redirection_file = strdup(filename);
    else 
        command->redirection_file = NULL;
}

char* handle_redirection(char **tokens, t_cmd *current, int *i, int tokens_length)
{
    if (*i >= tokens_length) 
    {
        fprintf(stderr, "Erreur : Index hors des limites du tableau.\n");
        return NULL;
    }
    char *redirection = tokens[*i];
    // printf("Redirection détectée: %s\n", redirection);

    if (*i + 1 < tokens_length && tokens[*i + 1] && (tokens[*i + 1][0] == '>' || tokens[*i + 1][0] == '<'))    
    {
        size_t combined_size = strlen(redirection) + strlen(tokens[*i + 1]) + 1;
        char *combined = malloc(combined_size);
        strcpy(combined, redirection);
        strcat(combined, tokens[*i + 1]);
        redirection = combined; // Mettre à jour le pointeur
        (*i)++; // Mettre à jour l'index i pour sauter le token de redirection combiné
    }
    // Incrémenter l'index i pour obtenir le nom du fichier pour la redirection
    (*i)++;
    char *filename = tokens[*i];
    if (!filename || strlen(filename) == 0) 
    {
        fprintf(stderr, "Erreur : Redirection sans fichier cible.\n");
        free(redirection);
        return NULL;
    }

     if (strcmp(redirection, ">") == 0)
    {
        set_redirection(current, filename, REDIR_OUTPUT);
        current->dup_number = 1;
        current->redirection_cmd = strdup("");
    }
    else if (strcmp(redirection, "<") == 0)
    {
        set_redirection(current, filename, REDIR_INPUT);
        current->dup_number = 0;
        current->redirection_cmd = strdup("");
    }
    else if (strcmp(redirection, ">>") == 0)
        set_redirection(current, filename, REDIR_APPEND);
    else if (strcmp(redirection, "<<") == 0)
        set_redirection(current, filename, REDIR_HEREDOC);
    free(redirection);
    // printf("Token après redirection: %s\n", filename);
    return filename;
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

t_cmd* parse_input_from_tokens(char** tokens)
{
    t_cmd *head = NULL, *current = NULL;
    int i = 0;
    if (tokens[0] && (tokens[0][0] == '>' || tokens[0][0] == '<')) 
    {
        // Créez une commande par défaut ou vide
        current = create_command("true");
        head = current;
    }
    // Calculez la longueur de tokens ici
    int tokens_length = 0;
    while (tokens[tokens_length] != NULL) 
        tokens_length++;
    while (tokens[i] != NULL) 
    {
        char* token = tokens[i];
        // printf("Token parse_input_from_tokens: %s\n", token);
        // printf("token = %s\n",token);
        if (strcmp(token, "|") == 0) 
        {
            // Si nous rencontrons un pipe, nous passons au token suivant et créons une nouvelle commande
            i++;
            token = tokens[i];
            t_cmd *new_command = create_command(token);
            if (current) 
                current->next = new_command;
            else 
                head = new_command;
            current = new_command;
        } 
        else if (token[0] == '>' || token[0] == '<') 
            handle_redirection(tokens, current, &i, tokens_length);  
        else 
        {
            if (!current) 
            {
                current = create_command(token);
                if (!head) 
                    head = current;
            } 
            else 
                add_argument(current, token);
        }
        i++;
    }
    return head;
}

void free_command(t_cmd *command) 
{
    if (command->name) 
        free(command->name);
    for (int i = 0; i < command->arg_count; i++) 
        free(command->args[i]);
    free(command->args);
    if (command->redirection_file) 
        free(command->redirection_file);
    if (command->redirection_cmd) 
        free(command->redirection_cmd);
    for (int i = 0; i < command->redirection_arg_count; i++) 
        free(command->redirection_args[i]);
    free(command->redirection_args);
    free(command);
}
