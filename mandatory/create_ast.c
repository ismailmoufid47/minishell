#include "shell.h"


t_ast	*create_ast_node(t_list *list)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		exit(1); ///need some free and error printing
	node->type = list->type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*add_node_front(t_ast *root, t_ast *node)
{
	if (root == NULL)
		root = node;
	else
	{
		node->left = root;
		root = node;
	}
	return (root);
}

t_ast	*create_ast(t_list *list)
{
	t_ast	*root;
	t_ast	*node;
	t_list	*prev = NULL;

	root = NULL;
	while (list)
	{
		if (list->type == IN)
		{
			node = create_ast_node(list);
			node->file = list->next->value;
			node->cmd_right = list->next->next->value;
			root = add_node_front(root, node);
		}
		else if (list->type == OUT)
		{
			node = create_ast_node(list);
			node->file = list->next->value;
			node->cmd_left = list->next->next->value;
			root = add_node_front(root, node);
		}
		else if (list->type == PIPE)
		{
			node = create_ast_node(list);
			node->cmd_left = prev->value;
			node->cmd_right = list->next->value;
			root = add_node_front(root, node);
		}
		prev = list;
		list = list->next;
	}
	return (root);
}
