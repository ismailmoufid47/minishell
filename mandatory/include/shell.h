#ifndef SHELL_H
# define SHELL_H


# include "../../libft/include/libft.h"
# include <stdio.h>    		    		// printf
# include <stdlib.h>        			// malloc, free, exit, getenv
# include <sys/stat.h>       			// stat, lstat, fstat
# include "readline/readline.h" 		// readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include "readline/history.h"  		// rl_clear_history, add_history
# include "ncurses/ncurses.h"			// ncurses, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
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
# include <sys/wait.h>					// wait, waitpid, WIFEXITED, WEXITSTATUS, WTERMSIG
#include <termios.h>

extern char	**environ;

typedef struct s_envp{
	char			*name;
	char			*value;
	struct s_envp	*next;
}	t_envp;

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
	int 			here_doc;
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
char	*get_cwd(t_envp *envp);
void	print_envp(char **envp);
void	print_argument(char **argv);
void	pwd(t_envp *envp, t_list *current, t_list *prev);
void	cd(char **args, t_envp	*envp, t_list *current, t_list *prev);
void	export(char **args, t_envp *envp, t_list *current, t_list *prev);
void	unset(char **args, t_envp *envp, t_list *current, t_list *prev);
void	exit_cmd(char **args, t_envp *envp, t_list *current, t_list *prev);

// envp:
t_envp	*set_envp(void);
char	*ft_get_env_val(t_envp *envp, char *var_name);
t_envp	*create_envp_node(char *var);
char	**envp_to_char(t_envp *envp);
t_envp	*remove_envp_var(t_envp *envp, char *name);
t_envp	*replace_missing_envp(t_envp *envp);

// Signal handelers:
void	print_prompt(int sig);

// wrappers: 
int		open_wrapper(char *file, int open_mode, int create_permissions);
void	pipe_wrapper(int *pipe_fd);
void	ft_dup2(int fd1, int fd2);
void	close_2(int fd1, int fd2);
pid_t	fork_wrapper(t_envp *envp);

// Errors: 
void	error(char *error_prefix);
void	exec_error(t_list **cmd);
void	identifier_error(char *cmd, char *identifier, t_envp *envp);
int		syntax_error(char **tokens, char *error_prefix, t_envp *envp);
void	error_fork(t_envp *envp);

//tokenize utils:
int		is_special_token(char *token);
int		is_special_operator(char c);
int		is_double_symbol(char *input, int pos);
void	skip_quoted_section(char *input, int *pos, char quote);
int		validate_tokens(char **tokens, t_envp *envp);

// classed list utils:
t_list	*keep_only_redirections(t_list *head);
t_list	*redirections(t_list *node, t_list *cmd);
t_list	*closest_cmd(t_list *head);
t_list	*token_to_node(t_list **head, t_list **nav, char *token, int type);

// execute utils:
void	redirect(t_list *cmd);

// Handle here-documents:
void	handle_here_doc(char *delimiter, t_envp *envp, int out);

// Built-ins utils:
void	is_bin(t_list *cmd, t_envp *envp);
int		is_valid_export_argument(char *arg);
int		is_valid_unset_argument(char *arg);
int		is_numeric(char *arg);

// command line Utils:
char	*get_prompt(t_envp *envp);
void	load_history(int fd);

// Free resources:
void	free_envp(t_envp *envp);
void	free_list(t_list *list);

#endif
