#include "shell.h"

void	print_list(t_list *list)
{
	printf("\t\tLIST\n");
	while (list)
	{
		if (list->type == IN)
			printf("IN: %s", list->value);
		else if (list->type == OUT)
			printf("OUT: %s", list->value);
		else if (list->type == PIPE)
			printf("PIPE: %s", list->value);
		else if (list->type == FIL)
			printf("FILE: %s", list->value);
		else
			printf("WORD: %s", list->value);
		list = list->next;
		if (list)
			printf(" ---> ");
	}
}
t_list	*create_node(char *value, t_node_type type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_list	*create_list(char **tokens)
{
	t_list	*nav = NULL;
	t_list	*list = NULL;
	t_list	*tmp;
	int		i;

	i = 0;
	nav = list;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<"))
		{
			if (nav == list)
			{
				list = create_node(tokens[i], IN);
				nav = list;
			}
			nav->next = create_node(tokens[i], IN);
		}
		else if (!ft_strcmp(tokens[i], ">"))
		{
			if (nav == list)
			{
				list = create_node(tokens[i], OUT);
				nav = list;
			}
			nav->next = create_node(tokens[i], OUT);
		}
		else if (!ft_strcmp(tokens[i], "|"))
		{
			if (nav == list)
			{
				list = create_node(tokens[i], PIPE);
				nav = list;
			}
			nav->next = create_node(tokens[i], PIPE);
		}
		else if (i != 0 && (!ft_strcmp(tokens[i - 1], "<") || !ft_strcmp(tokens[i - 1], ">")))
		{
			if (nav == list)
			{
				list = create_node(tokens[i], FIL);
				nav = list;
			}
			nav->next = create_node(tokens[i], FIL);
		}
		else
		{
			if (nav == list)
			{
				list = create_node(tokens[i], WRD);
				nav = list;
			}
			nav->next = create_node(tokens[i], WRD);
		}
		printf("token : %s node : %s\n", tokens[i], nav->value);
		nav = nav->next;
		i++;
	}
	tmp = list;
	list = list->next;
	free(tmp);
	return (list);
}
