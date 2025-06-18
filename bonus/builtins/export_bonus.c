#include "../include/shell_bonus.h"

int	is_valid_export_argument(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) || arg[0] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_export_args(t_envp *envp, char **args, int io[2], int *i)
{
	t_envp	*node;

	*i = 1;
	while (args[*i])
	{
		if (!is_valid_export_argument(args[*i]))
		{
			ft_dup2(io[0], STDIN_FILENO);
			ft_dup2(io[1], STDOUT_FILENO);
			return (identifier_error("export", args[*i], envp), 0);
		}
		free(envp->value);
		envp->value = ft_strdup("0");
		if (ft_strchr(args[*i], '='))
		{
			*(ft_strchr(args[*i], '=')) = '\0';
			envp = remove_envp_var(envp, args[*i]);
			node = create_envp_node(args[*i]);
			node->next = envp->next;
			envp->next = node;
		}
		(*i)++;
	}
	return (1);
}

void	export(char **args, t_envp *envp, t_list *current, t_list *prev)
{
	int		i;
	int		io[2];

	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	if (!prev && !current->next)
		redirect(current);
	i = 1;
	if (!handle_export_args(envp, args, io, &i))
		return ;
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
	ft_dup2(io[0], STDIN_FILENO);
	ft_dup2(io[1], STDOUT_FILENO);
}
