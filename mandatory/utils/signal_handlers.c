#include "../include/shell.h"

void	sig_int(int signum)
{
	(void)signum;
	exit(130);
}

void	print_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
