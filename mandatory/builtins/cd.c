#include "../include/shell.h"

#define FOUND_PWD     1
#define FOUND_OLDPWD  2 

void	set_pwds(t_envp *envp, t_envp *prev, int missing, char *old_pwd)
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

void	cd(char **args, t_envp	*envp, t_list *current, t_list *prev)
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
	while (envp)
	{
		if (!ft_strcmp(envp->name, "PWD"))
		{
			vars_found |= FOUND_PWD;
			free(envp->value);
			envp->value = getcwd(NULL, 0);
		}
		if (!ft_strcmp(envp->name, "OLDPWD"))
		{
			vars_found |= FOUND_OLDPWD;
			free(envp->value);
			envp->value = ft_strdup(old_pwd);
		}
		prev_envp = envp;
		envp = envp->next;
	}
	set_pwds(envp, prev_envp, vars_found, old_pwd);
}
