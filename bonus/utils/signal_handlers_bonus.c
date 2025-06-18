#include "../include/shell_bonus.h"

extern int	g_signal;

void	print_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = SIGINT;
}
