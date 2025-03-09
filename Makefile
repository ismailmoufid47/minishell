# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 20:55:12 by jbelkerf          #+#    #+#              #
#    Updated: 2025/03/07 21:20:20 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

CC=cc 
CFLAG= -wall -wextra -werror
LFLAG= -I/Users/jbelkerf/.brew/opt/readline/include/ 

SRC=shell.c

all:shell
	$(CC) $(CFLAG) $(SRC) -o $(NAME)