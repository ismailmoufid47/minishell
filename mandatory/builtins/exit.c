/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   exit.c                                              :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	exit_numeric_error(char *arg, t_envp *envp, int subshell)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free(envp->value);
	envp->value = ft_strdup("255");
	if (!subshell)
		exit(255);
}

void	exit_too_many_args(t_envp *envp)
{
	free(envp->value);
	envp->value = ft_strdup("1");
	ft_putendl_fd("Minishell: exit: too many arguments", 2);
}

void	exit_with_status(t_envp *envp, int status, int subshell)
{
	free(envp->value);
	envp->value = ft_itoa(status);
	if (!subshell)
		exit(status);
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
