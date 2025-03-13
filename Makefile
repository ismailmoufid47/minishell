NAME = minishell

# use this command to copy all the files in mandatory:
#find mandatory -type f | pbcopy

LIBFT_SRC =  libft/include/libft.h \
		libft/Makefile \
		libft/src/ft_atoi.c \
		libft/src/ft_bzero.c \
		libft/src/ft_calloc.c \
		libft/src/ft_isalnum.c \
		libft/src/ft_isalpha.c \
		libft/src/ft_isascii.c \
		libft/src/ft_isdigit.c \
		libft/src/ft_isprint.c \
		libft/src/ft_isspace.c \
		libft/src/ft_itoa.c \
		libft/src/ft_memchr.c \
		libft/src/ft_memcmp.c \
		libft/src/ft_memcpy.c \
		libft/src/ft_memmove.c \
		libft/src/ft_memset.c \
		libft/src/ft_printf.c \
		libft/src/ft_putchar_fd.c \
		libft/src/ft_putendl_fd.c \
		libft/src/ft_putnbr_fd.c \
		libft/src/ft_putstr_fd.c \
		libft/src/ft_split.c \
		libft/src/ft_strchr.c \
		libft/src/ft_strcmp.c \
		libft/src/ft_strdup.c \
		libft/src/ft_striteri.c \
		libft/src/ft_strjoin.c \
		libft/src/ft_strlcat.c \
		libft/src/ft_strlcpy.c \
		libft/src/ft_strlen.c \
		libft/src/ft_strmapi.c \
		libft/src/ft_strncmp.c \
		libft/src/ft_strnstr.c \
		libft/src/ft_strrchr.c \
		libft/src/ft_strtrim.c \
		libft/src/ft_substr.c \
		libft/src/ft_tolower.c \
		libft/src/ft_toupper.c \
		libft/src/get_next_line.c \
		libft/src/get_next_line_utils.c \
		libft/src/puthex.c \
		libft/src/putnbr.c \
		libft/src/putnbru.c \
		libft/src/putptr.c \
		libft/src/putstr.c


MANDATORY_FILES = mandatory/1_expansion/expand.c \
			mandatory/2_tokenization/tokenize.c \
			mandatory/2_tokenization/tokenize_utils.c \
			mandatory/3_listification/classed_list.c \
			mandatory/3_listification/classed_list_utils.c \
			mandatory/4_execution/execute.c \
			mandatory/4_execution/execute_utils.c \
			mandatory/Makefile \
			mandatory/bin/Makefile \
			mandatory/bin/echo.c \
			mandatory/bin/pwd.c \
			mandatory/shell.c \
			mandatory/include/shell.h \
			mandatory/utils/cmdline_utils.c \
			mandatory/utils/errors.c \
			mandatory/utils/wrappers.c \
			mandatory/utils/envp_handler.c


BONUS_FILES = 

all: $(NAME)

$(NAME): $(MANDATORY_FILES) $(LIBFT_SRC)
	make -C mandatory
	cp mandatory/minishell .
	cp -r mandatory/bin .

bonus: $(BONUS_FILES)
	make -C bonus
	cp bonus/minishell $(NAME)

clean:
	make -C mandatory clean
	make -C bonus clean

fclean:
	make -C mandatory fclean
# 	make -C bonus fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus