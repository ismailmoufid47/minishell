#ifndef SHELL_H
# define SHELL_H

# define O_W O_WRONLY
# define O_C O_CREAT
# define O_T O_TRUNC

# include "../../libft/include/libft.h"
# include <stdio.h>    		    
# include <stdlib.h>        	
# include <sys/stat.h>       	
# include "readline/readline.h" 
# include "readline/history.h"  
# include "ncurses/ncurses.h"	
# include <unistd.h>         	
# include <string.h>         	
# include <signal.h>         	
# include <dirent.h>         	
# include <sys/types.h>      	
# include <fcntl.h>          	
# include <sys/ioctl.h>      	
# include <termios.h>        	
# include <term.h>           	
# include <errno.h>          	
# include <sys/wait.h>			
# include <termios.h>

extern char				**environ;
typedef struct termios	t_term;

typedef struct s_envp
{
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
	int				redirected;
	struct s_list	*redirs;
	char			**args;
	int				pid;
	int				pipe_fds[2];
	int				here_doc;
	struct s_list	*next;
}	t_list;

//to be deleted
void	print_tokens(char **tokens);
void	print_list(t_list *list, int tab_count);

//expander:
char	*expand_env_variable(char *cmd_line, t_envp *envp, int is_here_doc);

// tokenize:
char	**tokenize(char *cmd);

//classed list:
t_list	*create_list(t_list *head, t_list *nav, char **tokens);

// Execute:
void	execute(t_list *list, t_envp *envp);

// Built-ins:
char	*get_cwd(t_envp *envp);
void	env_cmd(char **envp);
void	echo_cmd(char **argv);
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
void	error_fork(t_envp *envp);
void	identifier_error(char *cmd, char *identifier, t_envp *envp);
int		syntax_error(char **tokens, char *error_prefix, t_envp *envp);
void	exit_numeric_error(char *arg, t_envp *envp, int subshell);
void	exit_with_status(t_envp *envp, int status, int subshell);
void	exit_too_many_args(t_envp *envp);

// exec errors:
void	is_directory_error(t_list *cmd);
void	no_such_file_error(t_list *cmd);
void	permission_denied_error(t_list *cmd);
void	command_not_found_error(t_list *cmd);

// expand utils:
char	**ft_split_and_add_quotes(char *var, int is_here_doc);
char	*join_split_result(char *cmd, char **split, int start, int varln);

//tokenize utils:
int		is_single_operator(char c);
int		is_special_token(char *token);
int		handle_special_token(const char *input,
			int i, int *count, int *special);
void	update_quote_flags(char c, int *sq_flag, int *dq_flag);
int		validate_tokens(char **tokens, t_envp *envp);

// classed list utils:
int		handle_special_node(char *token, t_list **head, t_list **nav);
t_list	*remove_red_and_add_it_to_cmd(t_list *head);
t_list	*handle_cmd_red(t_list *head, t_node_type type, int *changed);
t_list	*keep_only_redirections(t_list *head);
t_list	*redirs(t_list *node, t_list *cmd);
t_list	*closest_cmd(t_list *head);
int		count_args(t_list *cmd);
t_list	*token_to_node(t_list **head, t_list **nav, char *token, int type);

// execute utils:
void	redirect(t_list *cmd);
void	close_obsolete_fds(t_list *current, t_list *prev);

// Handle here-documents:
int		handle_here_docs(t_envp *envp, t_list *list);

// Built-ins utils:
void	is_bin(t_list *cmd, t_envp *envp);
void	execute_builtin(t_list *current, t_envp *envp, t_list *prev, int *b);
void	redirect_builtins(t_list *current);
int		is_valid_export_argument(char *arg);
int		is_valid_unset_argument(char *arg);
int		is_numeric(char *arg);

// command line Utils:
char	*get_prompt(t_envp *envp);
void	load_history(int fd);

// Free resources:
void	free_envp(t_envp *envp);
void	free_list(t_list *list);

// string utils:
int		skip_spaces(const char *input, int i);

#endif
