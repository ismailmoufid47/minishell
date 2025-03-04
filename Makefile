NAME = minishell

MANDATORY_FILES = mandatory/Makefile mandatory/shell.h mandatory/shell.c \
				mandatory/expand.c mandatory/tokenize.c mandatory/errors.c \
				mandatory/wrappers.c mandatory/utils/cmdline_utils.c mandatory/utils/tokenize_utils.c \
				mandatory/bin/Makefile mandatory/bin/echo.c mandatory/bin/pwd.c

BONUS_FILES = 

all: $(NAME)

$(NAME): $(MANDATORY_FILES)
	make -C mandatory
	cp mandatory/minishell $(NAME)

bonus: $(BONUS_FILES)
	make -C bonus
	cp bonus/minishell $(NAME)

clean:
	make -C mandatory clean
	make -C bonus clean

fclean:
	make -C mandatory fclean
	make -C bonus fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus