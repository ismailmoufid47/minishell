
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

extern char	**environ;

typedef enum e_node_type
{
	PIPE,
	IN,
	OUT,
	HDOC,
	APP,
	FIL,
	CMD
}	t_node_type;

typedef struct s_envp{
	char			*name;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_list
{
	char			*value;
	struct s_list	*next;
	t_node_type		type;
	int				is_redirected;
	struct s_list	*redirections;
}	t_list;

// envp:
t_envp	*set_envp(void);
char	*ft_get_env_val(t_envp *envp, char *var_name);

// Wrapers: 
int		open_wraper(char *file, int open_mode, int create_permissions);

// Errors: 
void	error(char *error_prefix);
int		syntax_error(char **tokens, char *error_prefix);

// command line Utils:
char	*get_prompt(t_envp *envp);
void	load_history(const char *filename);

//expander:
char    *expand_env_variable(char *cmd_line, t_envp *envp);

// tokenize:
char	**tokenize(char *cmd);

//tokenize utils:
int		is_special_token(char *token);
int		is_special_operator(char c);
int		is_double_symbol(char *input, int pos);
void	skip_quoted_section(char *input, int *pos, char quote);
int		validate_tokens(char **tokens);

//classed list:
t_list	*create_list(char **tokens);

// classed list utils:
t_list	*keep_only_redirections(t_list *head);
t_list	*join_words(t_list *head);
void	print_list(t_list *list, int tab_count);
t_list	*redirections(t_list *node, t_list *cmd);
t_list	*closest_cmd(t_list *head);
t_list	*token_to_node(t_list **head, t_list **nav, char *token, int type);

// Execute:

#endif