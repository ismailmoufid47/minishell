#include "../include/shell.h"

extern int	g_signal;

void	print_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (g_signal != -1)
		g_signal = SIGINT;
	else
		g_signal = 0;
}
