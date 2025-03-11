#include "../include/shell.h"

void	redirect(t_list *cmd)
{
	t_list	*current;
	char	*file;
	char	*input;

	current = cmd->redirections;
	while (current)
	{
		file = current->next->value;
		if (current->type == IN)
			ft_dup2(open_wrapper(file, O_RDONLY, 0), 0);
		if (current->type == OUT)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT, 0200), 0);
		if (current->type == APP)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT | O_APPEND, 0200), 0);
		if (current->type == HDOC)
			handle_here_doc(file);
		current = current->next->next;
	}
}

void	execute(t_list *list, t_envp *envp)
{
	t_list	*current;

	current = list;
	while (current)
	{
		if (current->type == CMD && current->is_redirected)
			redirect(current);
		current = current->next;
	}
}
