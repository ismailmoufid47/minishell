/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:53:16 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/07 21:31:12 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit, getenv
# include <unistd.h>     // write, access, open, read, close, fork, getcwd, chdir, dup, dup2, isatty, ttyname, ttyslot
# include <sys/types.h>  // wait, waitpid, wait3, wait4, stat, lstat, fstat, opendir, readdir, closedir
# include <sys/wait.h>   // wait, waitpid, wait3, wait4
# include <sys/stat.h>   // stat, lstat, fstat
# include <fcntl.h>      // open, unlink
# include <dirent.h>     // opendir, readdir, closedir
# include <string.h>     // strerror
# include <signal.h>     // signal, sigaction, sigemptyset, sigaddset, kill
# include <termios.h>    // tcsetattr, tcgetattr
# include <curses.h>     // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (sometimes <ncurses.h> is needed)
# include <readline/readline.h>  // readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>   // add_history
# include <sys/ioctl.h> // ioctl

#endif