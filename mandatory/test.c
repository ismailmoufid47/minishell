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

void	token_to_node(t_list **head, t_list **nav, char *token, int type)
{
	if (!*head)
	{
		*head = create_node(token, type);
		*nav = *head;
	}
	else
	{
		(*nav)->next = create_node(token, type);
		*nav = (*nav)->next;
	}
}

t_list	*create_list(char **tokens)
{
	t_list	*nav;
	t_list	*head;
	t_list	*tmp;
	int		i;

	i = 0;
	nav = ((head = NULL), NULL);
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<"))
			token_to_node(&head, &nav, tokens[i], IN);
		else if (!ft_strcmp(tokens[i], ">"))
			token_to_node(&head, &nav, tokens[i], OUT);
		else if (!ft_strcmp(tokens[i], "|"))
			token_to_node(&head, &nav, tokens[i], PIPE);
		else if (i && (!ft_strcmp(tokens[i - 1], "<") || !ft_strcmp(tokens[i - 1], ">")))
			token_to_node(&head, &nav, tokens[i], FIL);
		else
			token_to_node(&head, &nav, tokens[i], WRD);
		printf("token : %s node : %s\n", tokens[i], nav->value);
		//printf("%p %p\n", nav->next, head);
		i++;
	}
	return (head);
}

int main(void)
{
	char *cmd_line;
	t_ast *root;
	char **tokens;
	t_list *list;

	cmd_line = "ls -l | wc -l";
	cmd_line = expand_env_variable(cmd_line);
	tokens = tokenize(cmd_line);
	list = create_list(tokens);
	print_list(list);
	return (0);
}
