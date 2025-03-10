NAME = minishell

# use this command to copy all the files in mandatory:
#find mandatory -type f | pbcopy


MANDATORY_FILES = mandatory/1_expansion/expand.c \
			mandatory/2_tokenization/tokenize.c \
			mandatory/2_tokenization/tokenize_utils.c \
			mandatory/3_listification/classed_list.c \
			mandatory/3_listification/classed_list_utils.c \
			mandatory/4_execution_tree_construction/create_ast.c \
			mandatory/Makefile \
			mandatory/bin/Makefile \
			mandatory/bin/echo.c \
			mandatory/bin/pwd.c \
			mandatory/shell.c \
			mandatory/include/shell.h \
			mandatory/utils/cmdline_utils.c \
			mandatory/utils/errors.c \
			mandatory/utils/wrappers.c


BONUS_FILES = 

all: $(NAME)

$(NAME): $(MANDATORY_FILES)
	make -C mandatory
	cp mandatory/minishell .
	cp mandatory/command_history .

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