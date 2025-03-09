NAME = minishell

# use this command to copy all the files in mandatory:
#find mandatory -type f | pbcopy

MANDATORY_FILES = mandatory/bin/echo.c \
				mandatory/bin/Makefile \
				mandatory/bin/pwd.c \
				mandatory/classed_list.c \
				mandatory/create_ast.c \
				mandatory/errors.c \
				mandatory/expand.c \
				mandatory/Makefile \
				mandatory/shell.c \
				mandatory/shell.h \
				mandatory/tokenize.c \
				mandatory/utils/classed_list_utils.c\
				mandatory/utils/cmdline_utils.c \
				mandatory/utils/tokenize_utils.c \
				mandatory/wrappers.c


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