
#include "shell.h"

char	*get_prompt(void)
{
	char	*user;
	char	*host;
	char	*pwd;
	char	*prompt;
	//int		fd;

	host = "kali";
	// fd = open_wraper("/etc/hostname", O_RDONLY, 0);
	// host = get_next_line(fd);
	user = getenv("USER");
	pwd = getenv("PWD");
	prompt = ft_strjoin(user, "@");
	prompt = ft_strjoin(prompt, host);
	prompt = ft_strjoin(prompt, "  ");
	prompt = ft_strjoin(prompt, pwd);
	prompt = ft_strjoin(prompt, "  # ");
	return (prompt);
}
