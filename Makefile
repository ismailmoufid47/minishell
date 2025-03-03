NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

MANDATORY_FILES = mandatory/Makefile mandatory/shell.h mandatory/shell.c mandatory/expand.c \
				mandatory/tokenize.c mandatory/errors.c mandatory/wrappers.c mandatory/cmdline_utils.c \
				mandatory/bin/Makefile mandatory/bin/echo.c mandatory/bin/pwd.c

BONUS_FILES = 

all: .mandatory

$(NAME): all

.mandatory: mandatory/minishell
	cp mandatory/minishell minishell
	touch .mandatory



mandatory/minishell: $(MANDATORY_FILES)
	make -C mandatory

bonus/minishell:
	make -C bonus

clean:
	make -C mandatory clean
	make -C bonus clean

fclean:
	make -C mandatory fclean
	make -C bonus fclean
	rm -f minishell
	rm -f .mandatory
	rm -f .bonus

re: fclean all

.PHONY: all clean fclean re