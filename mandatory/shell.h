/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:26:44 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/01 18:53:47 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H


# include "../libft/include/libft.h"
# include <unistd.h>         // write, access, open, read, close, fork, getcwd, chdir, execve, dup, dup2, pipe, isatty, ttyname
# include <stdio.h>          // printf
# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>  // rl_clear_history, add_history
# include <string.h>         // strerror
# include <stdlib.h>         // malloc, free, exit, getenv
# include <signal.h>         // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>         // opendir, readdir, closedir
# include <sys/types.h>      // wait, waitpid, wait3, wait4, stat, lstat, fstat
# include <fcntl.h>          // open, unlink
# include <sys/ioctl.h>      // ioctl
# include <termios.h>        // tcsetattr, tcgetattr
# include <curses.h>         // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (alternative: <term.h>)
# include <term.h>           // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (alternative to <curses.h>)
# include <errno.h>          // perror


typedef enum node_type{
	SEQ,
	AND,
	OR,
	PIP,
	IN,
	OUT,
	SUB,
	CMD
}	t_node_type;

typedef struct ast
{
	t_node_type	type;
	struct ast	*left;
	struct ast	*right;
	char		*file;
	char		*full_cmd;
}	t_ast;

// Wrapers: 
int	open_wraper(char *file, int open_mode, int create_permissions);

// Errors: 
void	error(char *error_prefix);

// command line Utils:
char	*get_prompt(void);

#endif