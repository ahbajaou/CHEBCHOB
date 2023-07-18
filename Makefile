
NAMES = minishell 
 
CFILES = main.c lexer.c power.c func.c exec.c exec_tools/*.c exec_tools/builtin/*.c

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -lreadline 

all :  $(NAMES)

$(NAMES) : $(CFILES)
			$(CC) $(CFLAGS) $(CFILES) -o minishell

clean : 
		$(RM) $(NAMES)

fclean : clean 

re : fclean all 