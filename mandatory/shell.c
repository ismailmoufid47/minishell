#include "shell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("Tokens:\n");
	while (tokens[i])
	{
		printf("	%d: %s\n", i, tokens[i]);
		i++;
	}
	printf("\n");
}

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
			node->cmd_left = prev->value;
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

t_ast	*parse(char *cmd_line)
{
	char	**tokens;
	t_ast	*root;
	t_list	*list;

	root = NULL;
	list = NULL;
	cmd_line = expand_env_variable(cmd_line);
	tokens = tokenize(cmd_line);
	list = create_list(tokens);
	root = create_ast(list);
	print_tokens(tokens);
	print_list(list);
	return (root);
}

void print_tree(t_ast *root)
{
	printf("\t\tTREE\n");
	while (root)
	{
		if (root->type == OUT)
		{
			printf("cmd %s --OUT---file %s\n", root->cmd_left, root->file);
			printf("\t\t|\n\t\t|\n");
		}
		else if (root->type == IN)
		{
			printf("cmd %s --IN---file %s\n", root->cmd_right, root->file);
			printf("\t\t|\n\t\t|\n");
		}
		else if (root->type == PIPE)
		{
			printf("cmd %s --PIPE---cmd %s\n", root->cmd_left, root->cmd_right);
			printf("\t\t|\n\t\t|\n");
		}
		root = root->left;
	}
}

int	main(void)
{
	char	*input;
	// t_ast	*root;

	while (1)
	{
		input = readline(get_prompt());
		if (input == NULL)
			exit(0);
		if (*input)
			add_history(input);
		parse(input);
		print_tree(parse(input));
	}
	return (0);
}


        