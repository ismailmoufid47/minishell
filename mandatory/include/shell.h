
#ifndef SHELL_H
# define SHELL_H


# include "../../libft/include/libft.h"
# include <stdlib.h>         // malloc, free, exit, getenv
# include <unistd.h>         // write, access, open, read, close, fork, getcwd, chdir, execve, dup, dup2, pipe, isatty, ttyname
# include <stdio.h>          // printf
# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>  // rl_clear_history, add_history
# include <string.h>         // strerror
# include <signal.h>         // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>         // opendir, readdir, closedir
# include <sys/types.h>      // wait, waitpid, wait3, wait4, stat, lstat, fstat
# include <fcntl.h>          // open, unlink
# include <sys/ioctl.h>      // ioctl
# include <termios.h>        // tcsetattr, tcgetattr
# include <curses.h>         // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (alternative: <term.h>)
# include <term.h>           // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (alternative to <curses.h>)
# include <errno.h>          // perror
# include <sys/wait.h>

typedef enum node_type
{
	PIPE,
	IN,
	OUT,
	HDOC,
	APP,
	CMD,
	FIL,
	WRD
}	t_node_type;

typedef struct ast
{
	t_node_type	type;
	struct ast	*left;
	struct ast	*right;
	char		*file;
	char		*cmd;
}	t_ast;

typedef struct a_list
{
	char			*value;
	struct a_list	*next;
	t_node_type		type;
	int				is_redirected;
	struct a_list	*redirections;
}	t_list;

// Wrapers: 
int		open_wraper(char *file, int open_mode, int create_permissions);

// Errors: 
void	error(char *error_prefix);

// command line Utils:
char	*get_prompt(void);
void	load_history(const char *filename);

//expander
char	*expand_env_variable(char *cmd_line);

//tokenize
int		is_special_operator(char c);
int		is_double_symbol(char *input, int pos);
void	skip_quoted_section(char *input, int *pos, char quote);
void	skip_whitespace(char *input, int *pos);
char	**tokenize(char *cmd);

//classed list
t_list	*create_list(char **tokens);
t_list	*join_words(t_list *head);
void	print_list(t_list *list, int tab_count);

//AST TREE
t_ast	*create_ast(t_list *list);


#endif