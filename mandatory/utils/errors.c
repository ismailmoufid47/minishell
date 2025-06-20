/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   errors.c                                            :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	error(char *error_prefix)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(error_prefix);
	free(error_prefix);
	exit(EXIT_FAILURE);
}

void	error_fork(t_envp *envp)
{
	ft_putstr_fd("Minishell: ", 2);
	perror("fork");
	free(envp->value);
	envp->value = ft_strdup("1");
}

int	syntax_error(char **tokens, char *error_prefix, t_envp *envp)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_prefix, 2);
	ft_putendl_fd("'", 2);
	ft_free_split(tokens);
	free(envp->value);
	envp->value = ft_strdup("258");
	return (0);
}

void	identifier_error(char *cmd, char *identifier, t_envp *envp)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(envp->value);
	envp->value = ft_strdup("1");
}

void	exec_error(t_list **cmd)
{
	if (!cmd || !*cmd)
		return ;
	is_directory_error(*cmd);
	no_such_file_error(*cmd);
	permission_denied_error(*cmd);
	command_not_found_error(*cmd);
}
