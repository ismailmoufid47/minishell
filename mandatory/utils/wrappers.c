
#include "../include/shell.h"

void	pipe_wrapper(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		error(ft_strdup("pipe"));
}

int	open_wrapper(char *file, int open_mode, int create_permissions)
{
	int	fd;

	if (!create_permissions)
		fd = open(file, open_mode);
	else
		fd = open(file, open_mode, create_permissions);
	if (fd == -1)
		error(ft_strdup("open"));
	return (fd);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error(ft_strdup("dup2"));
	close(fd1);
}

void	cd(char *full_cmd, t_envp	*envp)
{
	char	**args;
	char	*path;
	char	*old_pwd;

	args = split_zayda_naghza(full_cmd);
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

void	close_2(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
