#include "../include/shell.h"

void	unset(char **args, t_envp *envp, t_list *current, t_list *prev)
{
	int		i;

	redirect_builtins(current);
	i = 1;
	if (args[i] && !is_valid_unset_argument(args[i]))
		return (identifier_error("unset", args[i], envp));
	free(envp->value);
	envp->value = ft_strdup("0");
	if ((prev && prev->type == PIPE)
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
	int	subshell;

	redirect_builtins(current);
	subshell = ((ft_putendl_fd("exit", 1)), (prev && prev->type == PIPE)
			|| (current->next && current->next->type == PIPE));
	if (!args[1])
	{
		free(envp->value);
		envp->value = ft_strdup("0");
		if (!subshell)
			exit(0);
		return ;
	}
	if (!args[2])
	{
		if (is_numeric(args[1]))
			exit_with_status(envp, ft_atoi(args[1]) % 256, subshell);
		else
			exit_numeric_error(args[1], envp, subshell);
		return ;
	}
	if (is_numeric(args[1]))
		exit_too_many_args(envp);
	else
		exit_numeric_error(args[1], envp, subshell);
}
