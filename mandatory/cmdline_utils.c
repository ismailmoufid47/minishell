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
	char	buffer[256];
	ssize_t	count;

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
		count = read(fd[0], buffer, sizeof(buffer) - 1);
		if (count < 0)
			error("read");
		buffer[count] = '\0';
		close(fd[0]);
		wait(NULL);
		if (strchr(buffer, '.'))
			buffer[strchr(buffer, '.') - buffer] = '\0';
		else
			buffer[strchr(buffer, '\n') - buffer] = '\0';
	}
	return (ft_strdup(buffer));
}

char	*get_prompt(void)
{
	char	*user;
	char	*host;
	char	*pwd;
	char	*prompt;

	user = getenv("USER");
	host = get_host_name();
	pwd = getenv("PWD");
	prompt = ft_strjoin("\033[1;34m", user);
	prompt = ft_strjoin(prompt, "\033[1;37m@");
	prompt = ft_strjoin(prompt, "\033[1;34m");
	prompt = ft_strjoin(prompt, host);
	prompt = ft_strjoin(prompt, "\033[0m ");
	prompt = ft_strjoin(prompt, "\033[1;32m");
	prompt = ft_strjoin(prompt, pwd);
	prompt = ft_strjoin(prompt, "\033[0m $ ");
	return (prompt);
}
