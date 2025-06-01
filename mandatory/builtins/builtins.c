#include "../include/shell.h"

void  redirect_builtins(t_list *current)
{
	int	stdout_fd;
	int	stdin_fd;

	if (!current->is_redirected)
		return ;
	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	redirect(current);
	ft_dup2(stdout_fd, STDOUT_FILENO);
	ft_dup2(stdin_fd, STDIN_FILENO);
}

void	export(char **args, t_envp *envp, t_list *current, t_list *prev)
{
	int		i;
	t_envp	*node;
	int 	in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (!prev && !current->next)
		redirect(current);
	i = 1;
	while (args[i])
	{
		if (!is_valid_export_argument(args[i]))
		{
			ft_dup2(in, STDIN_FILENO);
			ft_dup2(out, STDOUT_FILENO);
			return (identifier_error("export", args[i], envp));
		}
		free(envp->value);
		envp->value = ft_strdup("0");
		if (ft_strchr(args[i], '='))
		{
			*(ft_strchr(args[i], '=')) = '\0';
			envp = remove_envp_var(envp, args[i]);
			node = create_envp_node(args[i]);
			node->next = envp->next;
			envp->next = node;
		}
		i++;
	}
	if (i == 1)
	{
		envp = envp->next;
		while (envp)
		{
			if (envp->name && envp->value)
				printf("declare -x %s=\"%s\"\n", envp->name, envp->value);
			envp = envp->next;
		}
	}
	ft_dup2(in, STDIN_FILENO);
	ft_dup2(out, STDOUT_FILENO);
}

void	cd(char **args, t_envp	*envp, t_list *current, t_list *prev)
{
	struct stat	dir;
	char	*path;
	char	*old_pwd;
	int		old_pwd_set;
	t_envp	*prev_envp;

	old_pwd_set = 0;
	redirect_builtins(current);
	path = args[1];
	if (!path)
		path = "/";
	stat(path, &dir);
	if (!S_ISDIR(dir.st_mode))
	{
		chdir(path);
		free(envp->value);
		envp->value = ft_strdup("1");
		ft_putstr_fd("Minishell: cd: ", 2);
		perror(path);
		free(envp->value);
		envp->value = ft_strdup("1");
		return ;
	}
	chdir(path);
	free(envp->value);
	envp->value = ft_strdup("0");
	if ((prev &&  prev->type == PIPE)
		|| (current->next && current->next->type == PIPE))
		return ;
	old_pwd = get_cwd(envp);
	while (envp)
	{
		if (!strcmp(envp->name, "PWD"))
		{
			free(envp->value);
			envp->value = getcwd(NULL, 0);
		}
		if (!strcmp(envp->name, "OLDPWD"))
		{
			old_pwd_set = 1;
			free(envp->value);
			envp->value = old_pwd;
		}
		prev_envp = envp;
		envp = envp->next;
	}
	if (!old_pwd_set)
	{
		path = ft_strjoin("OLDPWD=", old_pwd);
		*(ft_strchr(path, '=')) = '\0';
		prev_envp->next = create_envp_node(path);
		free(old_pwd);
		free(path);
	}
}

void	unset(char **args, t_envp *envp, t_list *current, t_list *prev)
{
	int		i;


	redirect_builtins(current);
	i = 1;
	if (args[i] && !is_valid_unset_argument(args[i]))
			return (identifier_error("unset", args[i], envp));
	free(envp->value);
	envp->value = ft_strdup("0");
	if ((prev &&  prev->type == PIPE)
		|| (current->next && current->next->type == PIPE))
			return ;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "?"))
		{
			i++;
			continue ;
		}
		remove_envp_var(envp, args[i]);
		i++;
	}
}

void	exit_cmd(char **args, t_envp *envp, t_list *current, t_list *prev)
{
	int subshell;


	redirect_builtins(current);
	subshell = (prev &&  prev->type == PIPE)
		|| (current->next && current->next->type == PIPE);
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		free(envp->value);
		envp->value = ft_strdup("0");
		if (!subshell)
			exit(0);
	}
	else if (!args[2])
	{
		if (is_numeric(args[1]))
		{
			free(envp->value);
			envp->value = ft_itoa(ft_atoi(args[1]) % 256);
			if (!subshell)
				exit(ft_atoi(args[1]) % 256);
		}
		else
		{
			ft_putstr_fd("Minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free(envp->value);
			envp->value = ft_strdup("255");
			if (!subshell)
				exit(255);
		}
	}
	else if (is_numeric(args[1]))
	{
		free(envp->value);
		envp->value = ft_strdup("1");
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
	}
	else
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free(envp->value);
		envp->value = ft_strdup("255");
		if (!subshell)
			exit(255);
	}
}
