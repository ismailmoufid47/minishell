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
