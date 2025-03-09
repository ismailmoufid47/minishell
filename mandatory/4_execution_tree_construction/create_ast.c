#include "../include/shell.h"


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
	t_ast	*last_created_node;

	root = NULL;
	last_created_node = NULL;
	while (list)
	{
		if (list->type == IN)
		{
			node = create_ast_node(list);
			node->file = list->next->value;
		}
		else if (list->type == OUT)
		{
			node = create_ast_node(list);
			node->file = list->next->value;
			if (last_created_node && last_created_node->type != CMD)
				last_created_node->right = node;
			else if (!last_created_node)
				root = node;
		}
		else if (list->type == PIPE)
		{
			node = create_ast_node(list);
			root = add_node_front(root, node);
		}
		else if (list->type == CMD)
		{
			node = create_ast_node(list);
			node->type = CMD;
			node->cmd = list->value;
			if (last_created_node == NULL)
				root = node;
			else if (last_created_node->type == OUT)
				last_created_node->right = node;
			else if (last_created_node->type == PIPE)
				root->right = node;
		}
		last_created_node = node;
		list = list->next;
	}
	return (root);
}
