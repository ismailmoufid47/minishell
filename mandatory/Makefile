NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../libft/include \
         -I ~/.brew/opt/readline/include -I ~/.brew/opt/ncurses/include

LFLAGS = -L ../libft -L ~/.brew/opt/readline/lib -L ~/.brew/opt/ncurses/lib \
         -l ft -l readline -l ncurses


LIBFT = ../libft/libft.a 


SRC = 1_expansion/expand.c \
	2_tokenization/tokenize.c \
	2_tokenization/tokenize_utils.c \
	3_listification/linked_list.c \
	3_listification/linked_list_utils.c \
	4_execution_tree_construction/create_ast.c \
	utils/cmdline_utils.c \
	utils/wrappers.c \
	utils/errors.c \
	shell.c


all: $(NAME)

$(NAME): include/shell.h $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(NAME)
	mv -f ../command_history .

$(LIBFT):
	make -C ../libft

clean:
	make -C ../libft clean

fclean: clean
	rm -f $(NAME)
	make -C ../libft fclean

re: fclean all

.PHONY: all clean fclean re bonus