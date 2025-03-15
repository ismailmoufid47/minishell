#include "../include/shell.h"

void	export(char **args, t_envp *envp)
{
	int		i;
	t_envp	*node;

	i = 1;
	while (args[i])
	{
		if (!is_valid_export_argument(args[i]))
			export_error(args[i]);
		else if (ft_strchr(args[i], '='))
		{
			*(ft_strchr(args[i], '=')) = '\0';
			envp = remove_envp_var(envp, args[i]);
			node = create_envp_node(args[i]);
			node->next = envp->next;
			envp->next = node;
		}
		i++;
	}
}

void	cd(char **args, t_envp	*envp)
{
	char	*path;
	char	*old_pwd;

	path = args[1];
	if (!path)
		path = "/";
	if (chdir(path) == -1)
	{
		free(envp->value);
		envp->value = ft_strdup("1");
		ft_putstr_fd("Minishell: cd: ", 2);
		perror(path);
		ft_free_split(args);
		return ;
	}
	ft_free_split(args);
	old_pwd = get_cwd(envp);
	while (envp)
	{
		if (!strcmp(envp->name, "PWD"))
			envp->value = ft_strdup(getcwd(NULL, 0));
		if (!strcmp(envp->name, "OLDPWD"))
		{
			free(envp->value);
			envp->value = old_pwd;
		}
		envp = envp->next;
	}
}

