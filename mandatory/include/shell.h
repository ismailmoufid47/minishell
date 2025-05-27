
#ifndef SHELL_H
# define SHELL_H


# include "../../libft/include/libft.h"
# include <stdio.h>    		    		// printf
# include "readline/readline.h" 		// readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include "readline/history.h"  		// rl_clear_history, add_history
# include "ncurses/ncurses.h"
# include <stdlib.h>        			// malloc, free, exit, getenv
# include <unistd.h>         			// write, access, open, read, close, fork, getcwd, chdir, execve, dup, dup2, pipe, isatty, ttyname
# include <string.h>         			// strerror
# include <signal.h>         			// signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>         			// opendir, readdir, closedir
# include <sys/types.h>      			// wait, waitpid, wait3, wait4, stat, lstat, fstat
# include <fcntl.h>          			// open, unlink
# include <sys/ioctl.h>      			// ioctl
# include <termios.h>        			// tcsetattr, tcgetattr
# include <term.h>           			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (alternative to <curses.h>)
# include <errno.h>          			// perror
# include <sys/wait.h>
#include <termios.h>

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

typedef enum e_quotation
{
	UNQUOTED,
	DOQUOTED,
	SIQUOTED
}	t_quotation;

typedef struct s_envp{
	char			*name;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_list
{
	t_node_type		type;
	char			*value;
	t_quotation		quote_type;
	int				is_redirected;
	struct s_list	*redirections;
	char			**args;
	int				pid;
	int				pipe_fds[2];
	struct s_list	*next;
}	t_list;

//to be deleted
void	print_tokens(char **tokens);
void	print_list(t_list *list, int tab_count);

//expander:
char	*expand_env_variable(char *cmd_line, t_envp *envp);

// tokenize:
char	**tokenize(char *cmd);

//classed list:
t_list	*create_list(char **tokens);

// Execute:
void	execute(t_list *list, t_envp **envp);

// Built-ins:
void	pwd(t_envp *envp);
void	cd(char **args, t_envp	*envp);
void	export(char **args, t_envp *envp);
void	unset(char **args, t_envp *envp);
void	exit_cmd(char **args, t_envp *envp, t_list *list);

// envp:
t_envp	*set_envp(void);
char	*ft_get_env_val(t_envp *envp, char *var_name);
t_envp	*create_envp_node(char *var);
char	**envp_to_char(t_envp *envp);
t_envp	*remove_envp_var(t_envp *envp, char *name);

// Signal handelers:
void	print_prompt(int sig);

// wrappers: 
int		open_wrapper(char *file, int open_mode, int create_permissions);
void	pipe_wrapper(int *pipe_fd);
void	ft_dup2(int fd1, int fd2);
void	close_2(int fd1, int fd2);

// Errors: 
void	error(char *error_prefix);
void	command_not_found(char *cmd);
void	export_error(char *identifier);
int		syntax_error(char **tokens, char *error_prefix);
void	error_fork(t_envp **envp, char *error_prefix);

//tokenize utils:
int		is_special_token(char *token);
int		is_special_operator(char c);
int		is_double_symbol(char *input, int pos);
void	skip_quoted_section(char *input, int *pos, char quote);
int		validate_tokens(char **tokens);

// classed list utils:
t_list	*keep_only_redirections(t_list *head);
t_list	*redirections(t_list *node, t_list *cmd);
t_list	*closest_cmd(t_list *head);
t_list	*token_to_node(t_list **head, t_list **nav, char *token, int type);

// execute utils:
void	handle_here_doc(char *delimiter, t_envp *envp);

// Built-ins utils:
char	*get_cwd(t_envp *envp);
int		is_bin(char *cmd);
int		is_valid_export_argument(char *arg);
int		is_numeric(char *arg);

// command line Utils:
char	*get_prompt(t_envp *envp);
void	load_history(int fd);

#endif
