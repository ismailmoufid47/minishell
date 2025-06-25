NAME = minishell

CC = cc

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

SRC = 1_expansion/expand_bonus.c \
	1_expansion/expand_heredoc_bonus.c \
	1_expansion/expand_utils_bonus.c \
	2_tokenization/tokenize_bonus.c \
	2_tokenization/tokenize_utils_bonus.c \
	3_wildcard/wildcard_bonus.c \
	3_wildcard/wildcard_utils_bonus.c \
	4_listification/classed_list_bonus.c \
	4_listification/classed_list_utils_bonus.c \
	4_listification/classed_list_redirections_bonus.c \
	5_execution/execute_bonus.c \
	5_execution/execute_utils_bonus.c \
	builtins/builtins_bonus.c \
	builtins/exit_bonus.c \
	builtins/export_bonus.c \
	builtins/cd_bonus.c \
	builtins/builtins_utils_bonus.c \
	utils/cmdline_utils_bonus.c \
	utils/envp_handler_bonus.c \
	utils/here_doc_handler_bonus.c \
	utils/envp_handler_utils_bonus.c \
	utils/signal_handlers_bonus.c \
	utils/free_resources_bonus.c \
	utils/wrappers_bonus.c \
	utils/errors_bonus.c \
	utils/exec_errors_bonus.c \
	utils/string_utils_bonus.c \
	shell_bonus.c

all: $(NAME)

$(NAME): include/shell_bonus.h $(LIBFT) $(LIBFT_SRC) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(NAME)

$(LIBFT):
	make -C ../libft

clean:
	make -C ../libft clean

fclean: clean
	rm -f $(NAME)
	make -C ../libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
