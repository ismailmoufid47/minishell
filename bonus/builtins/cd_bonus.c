/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   cd_bonus.c                                          :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

#define FOUND_PWD     1
#define FOUND_OLDPWD  2 

void	set_missing(t_envp *envp, t_envp *prev, int missing, char *old_pwd)
{
	char	*path;

	if (!(missing & FOUND_OLDPWD))
	{
		path = ft_strjoin("OLDPWD=", old_pwd);
		*(ft_strchr(path, '=')) = '\0';
		prev->next = create_envp_node(path);
		prev = prev->next;
		free(path);
	}
	free(old_pwd);
	if (!(missing & FOUND_PWD))
	{
		old_pwd = get_cwd(envp);
		path = ft_strjoin("PWD=", old_pwd);
		free(old_pwd);
		*(ft_strchr(path, '=')) = '\0';
		prev->next = create_envp_node(path);
		free(path);
	}
}

int	validate_path(t_envp *envp, char *path)
{
	struct stat	dir;

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
		return (0);
	}
	return (1);
}

void	update_pwds(t_envp *envp, t_envp **prev, int *missing, char *old_pwd)
{
	while (envp)
	{
		if (!ft_strcmp(envp->name, "PWD"))
		{
			*missing |= FOUND_PWD;
			free(envp->value);
			envp->value = getcwd(NULL, 0);
		}
		if (!ft_strcmp(envp->name, "OLDPWD"))
		{
			*missing |= FOUND_OLDPWD;
			free(envp->value);
			envp->value = ft_strdup(old_pwd);
		}
		*prev = envp;
		envp = envp->next;
	}
}

void	cd(char **args, t_envp *envp, t_list *current, t_list *prev)
{
	char		*path;
	char		*old_pwd;
	int			vars_found;
	t_envp		*prev_envp;

	redirect_builtins(current);
	path = args[1];
	if (!path)
		path = "/";
	if (!validate_path(envp, path))
		return ;
	free(envp->value);
	envp->value = ft_strdup("0");
	if ((prev && prev->type == PIPE)
		|| (current->next && current->next->type == PIPE))
		return ;
	old_pwd = get_cwd(envp);
	chdir(path);
	vars_found = 0;
	update_pwds(envp, &prev_envp, &vars_found, old_pwd);
	set_missing(envp, prev_envp, vars_found, old_pwd);
}
