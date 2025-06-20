NAME = minishell

#\
find mandatory -type f | pbcopy

#\
find bonus -type f | pbcopy

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

MANDATORY_FILES = mandatory/shell.c \
				mandatory/include/shell.h \
				mandatory/Makefile \
				mandatory/1_expansion/expand.c \
				mandatory/1_expansion/expand_heredoc.c \
				mandatory/1_expansion/expand_utils.c \
				mandatory/2_tokenization/tokenize.c \
				mandatory/2_tokenization/tokenize_utils.c \
				mandatory/3_listification/classed_list.c \
				mandatory/3_listification/classed_list_utils.c \
				mandatory/3_listification/classed_list_redirections.c \
				mandatory/4_execution/execute.c \
				mandatory/4_execution/execute_utils.c \
				mandatory/builtins/cd.c \
				mandatory/builtins/exit.c \
				mandatory/builtins/export.c \
				mandatory/builtins/builtins.c \
				mandatory/builtins/builtins_utils.c \
				mandatory/utils/cmdline_utils.c \
				mandatory/utils/envp_handler.c \
				mandatory/utils/envp_handler_utils.c \
				mandatory/utils/errors.c \
				mandatory/utils/exec_errors.c \
				mandatory/utils/free_resources.c \
				mandatory/utils/here_doc_handler.c \
				mandatory/utils/signal_handlers.c \
				mandatory/utils/string_utils.c \
				mandatory/utils/wrappers.c

			
BONUS_FILES = bonus/shell_bonus.c \
			bonus/include/shell_bonus.h \
			bonus/Makefile \
			bonus/1_expansion/expand_bonus.c \
			bonus/1_expansion/expand_utils_bonus.c \
			bonus/2_tokenization/tokenize_bonus.c \
			bonus/2_tokenization/tokenize_utils_bonus.c \
			bonus/3_wildcard/wildcard_bonus.c \
			bonus/3_wildcard/wildcard_utils_bonus.c \
			bonus/4_listification/classed_list_bonus.c \
			bonus/4_listification/classed_list_utils_bonus.c \
			bonus/4_listification/classed_list_redirections_bonus.c \
			bonus/5_execution/execute_bonus.c \
			bonus/5_execution/execute_utils_bonus.c \
			bonus/builtins/cd_bonus.c \
			bonus/builtins/exit_bonus.c \
			bonus/builtins/export_bonus.c \
			bonus/builtins/builtins_bonus.c \
			bonus/builtins/builtins_utils_bonus.c \
			bonus/utils/cmdline_utils_bonus.c \
			bonus/utils/envp_handler_bonus.c \
			bonus/utils/envp_handler_utils_bonus.c \
			bonus/utils/errors_bonus.c \
			bonus/utils/exec_errors_bonus.c \
			bonus/utils/free_resources_bonus.c \
			bonus/utils/here_doc_handler_bonus.c \
			bonus/utils/signal_handlers_bonus.c \
			bonus/utils/string_utils_bonus.c \
			bonus/utils/wrappers_bonus.c

all: $(NAME)

.mn_made: $(MANDATORY_FILES) $(LIBFT_SRC)
	make -C mandatory
	mv -f mandatory/minishell .
	rm -f .bn_made
	touch .mn_made

.bn_made: $(BONUS_FILES) $(LIBFT_SRC)
	make -C bonus
	mv -f bonus/minishell .
	rm -f .mn_made
	touch .bn_made

$(NAME): .mn_made


bonus: .bn_made

clean:
	make -C mandatory clean
	make -C bonus clean
m:
	make m -C mandatory
	mv -f mandatory/minishell .

mb:
	make m -C bonus
	mv -f bonus/minishell .

fclean:
	make -C mandatory fclean
	make -C bonus fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
