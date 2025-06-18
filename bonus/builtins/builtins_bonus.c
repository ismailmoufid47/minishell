#include "../include/shell_bonus.h"

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

void	echo_cmd(char **argv)
{
	int	i;

	i = 1;
	if (!ft_strcmp(argv[1], "-n"))
		i = 2;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(argv[1], "-n"))
		printf("\n");
}

void	env_cmd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	while (--i > 0)
		printf("%s\n", envp[i]);
	ft_free_split(envp);
}

char	*get_cwd(t_envp *envp)
{
	while (envp)
	{
		if (!ft_strcmp(envp->name, "PWD"))
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (getcwd(NULL, 0));
}
