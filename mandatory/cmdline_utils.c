#include "shell.h"

void	execute_hostname_command(const char *cmd, int fd[2])
{
	char	*args[2];

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error("dup2");
	close(fd[1]);
	args[0] = (char *)cmd;
	args[1] = NULL;
	if (execve(cmd, args, NULL) == -1)
		error("execve");
}

char	*get_host_name(void)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	line = NULL;
	if (pipe(fd) == -1)
		error("pipe");
	pid = fork();
	if (pid < 0)
		error("fork");
	else if (pid == 0)
		execute_hostname_command("/bin/hostname", fd);
	else
	{
		close(fd[1]);
		line = get_next_line(fd[0]);
		wait(NULL);
		close(fd[0]);
		if (!line)
			error("read");
		*ft_strchr(line, '\n') = '\0';
		if (ft_strchr(line, '.'))
			*ft_strchr(line, '.') = '\0';
	}
	return (line);
}

char	*replace_home_with_tilde(char *pwd)
{
	char	*home;
	size_t	home_len;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(pwd));
	home_len = ft_strlen(home);
	if (ft_strncmp(pwd, home, home_len) == 0)
		return (ft_strjoin("~", pwd + home_len));
	return (ft_strdup(pwd));
}

char	*get_prompt(void)
{
	char	*host;
	char	*pwd;
	char	*prmpt;
	char	*tmp;

	host = get_host_name();
	pwd = getenv("PWD");
	if (!pwd)
		pwd = ft_strdup("unknown");
	else
		pwd = replace_home_with_tilde(pwd);
	tmp = ((prmpt = ft_strjoin("\033[1;34m", getenv("USER"))), prmpt);
	tmp = ((prmpt = ft_strjoin(prmpt, "@")), free(tmp), prmpt);
	tmp = ((prmpt = ft_strjoin(prmpt, host)), free(tmp), free(host), prmpt);
	tmp = ((prmpt = ft_strjoin(prmpt, "\033[0m: \033[1;32m")), free(tmp), prmpt);
	tmp = ((prmpt = ft_strjoin(prmpt, pwd)), free(tmp), free(pwd), prmpt);
	prmpt = ((free(tmp)), ft_strjoin(prmpt, "\033[0m$ "));
	return (prmpt);
}
