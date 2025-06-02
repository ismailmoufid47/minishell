#include "../include/shell.h"

void	free_envp(t_envp *envp)
{
	if (!envp)
		return ;
	free(envp->name);
	free(envp->value);
	free_envp(envp->next);
	return (free(envp));
}

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->type == CMD)
		{
			ft_free_split(temp->args);
			if (temp->is_redirected)
				free_list(temp->redirections);
		}
		else
			free(temp->value);
		free(temp);
	}
}
