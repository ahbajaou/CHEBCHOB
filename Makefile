NAMES = minishell

CFILES = main.c lexer.c power.c power_continue.c power_free.c func.c exec.c exec_tools/*.c exec_tools/builtin/*.c dollar.c handle_error.c func2.c
 
CC = gcc -g

CFLAGS = -Wall -Wextra -Werror  -lreadline -fsanitize=address -g3

all :  $(NAMES)

$(NAMES) : $(CFILES)
			$(CC)  $(CFILES) $(CFLAGS)  -o minishell

clean : 
		$(RM) $(NAMES)

fclean : clean 

re : fclean all