CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../../libft/include\
         -I ~/.brew/opt/readline/include -I ~/.brew/opt/ncurses/include

LFLAGS = -L ../../libft -lft

LIBFT = ../../libft/libft.a 

SRC = ../utils/errors.c ../utils/envp_handler.c

NAME = bin

all: ../include/shell.h $(LIBFT) echo env pwd

$(NAME): all

echo: ../include/shell.h $(LIBFT) $(SRC) echo.c
	@$(CC) $(CFLAGS) $(SRC) echo.c $(LFLAGS) -o echo

env: ../include/shell.h $(LIBFT) $(SRC) env.c
	@$(CC) $(CFLAGS) $(SRC) env.c $(LFLAGS) -o env

pwd: ../include/shell.h $(LIBFT) $(SRC) pwd.c
	@$(CC) $(CFLAGS) $(SRC) pwd.c $(LFLAGS) -o pwd

$(LIBFT):
	@make -C ../../libft

clean:
	@make -C ../../libft clean

fclean: clean
	@rm -f pwd
	@rm -f echo
	@make -C ../../libft fclean

re: fclean all

.PHONY: all clean fclean re bin pwd
