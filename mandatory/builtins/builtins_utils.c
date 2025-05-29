#include "../include/shell.h"

int	is_bin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "pwd"));
}


char	*get_cwd(t_envp *envp)
{
	while (envp)
	{
		if (!ft_strcmp(envp->name, "PWD"))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

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

int	is_valid_unset_argument(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


int	is_numeric(char *arg)
{
	int		i;
	int		sign;
	long 	res;

	i = 0;
	sign = 1;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	res = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		 if (sign == 1 && (res * 10 + (arg[i] - '0')) * sign < res * sign)
			return (0);
		if (sign == -1 && (res * 10 + (arg[i] - '0')) * sign > res * sign)
			return (0);
		res = res * 10 + (arg[i] - '0');
		i++;
	}
	return (i);
}
