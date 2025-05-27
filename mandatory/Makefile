NAME = minishell

CC = cc

FSANITIZE = -fsanitize=address -g

CFLAGS = -Wall -Wextra -Werror -I ../libft/include \
         -I ~/.brew/opt/readline/include -I ~/.brew/opt/ncurses/include

LFLAGS = -L ../libft -L ~/.brew/opt/readline/lib -L ~/.brew/opt/ncurses/lib \
         -l ft -l readline -l ncurses


LIBFT = ../libft/libft.a 

LIBFT_SRC =  ../libft/include/libft.h \
		../libft/Makefile \
		../libft/src/ft_atoi.c \
		../libft/src/ft_bzero.c \
		../libft/src/ft_calloc.c \
		../libft/src/ft_isalnum.c \
		../libft/src/ft_isalpha.c \
		../libft/src/ft_isascii.c \
		../libft/src/ft_isdigit.c \
		../libft/src/ft_isprint.c \
		../libft/src/ft_isspace.c \
		../libft/src/ft_itoa.c \
		../libft/src/ft_memchr.c \
		../libft/src/ft_memcmp.c \
		../libft/src/ft_memcpy.c \
		../libft/src/ft_memmove.c \
		../libft/src/ft_memset.c \
		../libft/src/ft_printf.c \
		../libft/src/ft_putchar_fd.c \
		../libft/src/ft_putendl_fd.c \
		../libft/src/ft_putnbr_fd.c \
		../libft/src/ft_putstr_fd.c \
		../libft/src/ft_split.c \
		../libft/src/ft_strchr.c \
		../libft/src/ft_strcmp.c \
		../libft/src/ft_strdup.c \
		../libft/src/ft_striteri.c \
		../libft/src/ft_strjoin.c \
		../libft/src/ft_strlcat.c \
		../libft/src/ft_strlcpy.c \
		../libft/src/ft_strlen.c \
		../libft/src/ft_strmapi.c \
		../libft/src/ft_strncmp.c \
		../libft/src/ft_strnstr.c \
		../libft/src/ft_strrchr.c \
		../libft/src/ft_strtrim.c \
		../libft/src/ft_substr.c \
		../libft/src/ft_tolower.c \
		../libft/src/ft_toupper.c \
		../libft/src/get_next_line.c \
		../libft/src/get_next_line_utils.c \
		../libft/src/puthex.c \
		../libft/src/putnbr.c \
		../libft/src/putnbru.c \
		../libft/src/putptr.c \
		../libft/src/putstr.c

SRC = 1_expansion/expand.c \
	2_tokenization/tokenize.c \
	2_tokenization/tokenize_utils.c \
	3_listification/classed_list.c \
	3_listification/classed_list_utils.c \
	4_execution/execute.c \
	4_execution/execute_utils.c \
	builtins/builtins.c \
	builtins/builtins_utils.c \
	utils/cmdline_utils.c \
	utils/envp_handler.c \
	utils/signal_handlers.c \
	utils/wrappers.c \
	utils/errors.c \
	shell.c


all: $(NAME)

$(NAME): include/shell.h $(LIBFT) $(LIBFT_SRC) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS)  -o $(NAME) 

$(LIBFT):
	make -C ../libft

clean:
	make -C ../libft clean

fclean: clean
	rm -f $(NAME)
	make -C ../libft fclean

re: fclean all
m :fclean include/shell.h $(LIBFT) $(LIBFT_SRC) $(SRC) 
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS)  -o $(NAME) $(FSANITIZE)

.PHONY: all clean fclean re bonus
