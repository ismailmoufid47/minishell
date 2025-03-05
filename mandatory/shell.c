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
