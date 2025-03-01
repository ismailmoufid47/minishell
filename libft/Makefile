NAME = libft.a

SRC = src/ft_isalpha.c src/ft_isalnum.c src/ft_bzero.c src/ft_atoi.c src/ft_calloc.c src/ft_isascii.c \
	  src/ft_isdigit.c src/ft_isprint.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c \
	  src/ft_memset.c src/ft_strchr.c src/ft_strdup.c src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c \
	  src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c src/ft_tolower.c src/ft_toupper.c src/ft_substr.c \
	  src/ft_strtrim.c src/ft_strmapi.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c \
	  src/ft_split.c src/ft_striteri.c src/ft_strjoin.c src/ft_itoa.c src/ft_printf.c src/putstr.c \
	  src/putnbr.c src/puthex.c src/putptr.c src/putnbru.c src/get_next_line.c src/get_next_line_utils.c src/ft_strcmp.c 

OBJ = $(SRC:src/%.c=obj/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME): obj $(OBJ)
	@ar -rc $(NAME) $(OBJ)

all: $(NAME)

obj/%.o: src/%.c include/libft.h obj
	@$(CC) $(CFLAGS) -c $< -o $@

obj:
	@mkdir -p obj

clean:
	@rm -rf obj/

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus