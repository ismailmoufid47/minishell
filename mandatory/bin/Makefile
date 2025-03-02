CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../libft/include 

LFLAGS = -L ../../libft -l ft

LIBFT = ../../libft/libft.a 

SRC = ../errors.c

all: ../shell.h $(LIBFT) pwd

pwd: ../shell.h $(LIBFT) $(SRC) pwd.c
	@$(CC) $(CFLAGS) $(LFLAGS) $(SRC) pwd.c -o pwd

$(LIBFT):
	@make -C ../../libft

clean:
	make -C ../../libft clean

fclean: clean
	rm -f pwd
	make -C ../../libft fclean

re: fclean all

.PHONY: all clean fclean re bonus