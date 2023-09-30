NAMES = minishell

CFILES = main.c parse/*.c exec_tools/*.c exec_tools/builtin/*.c
 
CC = gcc -g

CFLAGS = -Wall -Wextra -Werror  -lreadline -fsanitize=address -g3

all :  $(NAMES)

$(NAMES) : $(CFILES)
			$(CC)  $(CFILES) $(CFLAGS)  -o minishell

clean : 
		$(RM) $(NAMES)

fclean : clean 

re : fclean all