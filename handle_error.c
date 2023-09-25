#include "minishell.h"

void error(ErrorType type) 
{
    if (type == ERROR_SYNTAX)
    {
        fprintf(stderr, "syntax error\n");

    }
    else if (type == ERROR_PIPE) 
        fprintf(stderr, "syntax error near unexpected token `|'.\n");
    else if (type == ERROR_DOUBLE_PIPE) 
        fprintf(stderr, "syntax error near unexpected token `||'.\n");
    else if (type == REDIR_ERROR) 
        fprintf(stderr, "syntax error near unexpected token `newline'\n");
    else if (type == REDIR_ERROR_L1R1) 
        fprintf(stderr, "syntax error near unexpected token `<>'\n");
    else if (type == ERROR_CNF)
        fprintf(stderr, "command not found\n");
    else 
        fprintf(stderr, "Oopsie daisy! We kinda forgot this one... 😅🛸\n");
}