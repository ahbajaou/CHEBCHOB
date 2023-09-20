
NAMES = minishell 
 
CFILES = main.c lexer.c power.c func.c exec.c exec_tools/*.c exec_tools/builtin/*.c dollar.c

CC = cc -g

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 -lreadline

all :  $(NAMES)

$(NAMES) : $(CFILES)
			$(CC) $(CFLAGS) $(CFILES)   -o minishell

clean : 
		$(RM) $(NAMES)

fclean : clean 

re : fclean all 