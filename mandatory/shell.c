#include "shell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("\n		TOKENS\n\n");
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
	printf("\nCMDLINE AFTER EXPANSION: %s\n\n", cmd_line);
	tokens = tokenize(cmd_line);
	print_tokens(tokens);
	list = create_list(tokens);
	print_list(list);
	// root = create_ast(list);
	return (root);
}

// void	print_tree(t_ast *root)
// {
// 	printf("\n		TREE\n\n");
// 	while (root)
// 	{
// 		if (root->type == OUT)
// 		{
// 			printf("	\033[1;31mcmd: %s\033[0m←\033[1;32mOUT\033[0m→\033[1;34mfile: %s\033[0m\n", root->left, root->file);
// 			printf("		↓\n");
// 		}
// 		else if (root->type == IN)
// 		{
// 			printf("	\033[1;31mcmd: %s\033[0m←\033[1;32mIN\033[0m→\033[1;34mfile: %s\033[0m\n",root->cmd_right, root->file);
// 			printf("		↓\n");
// 		}
// 		else if (root->type == PIPE)
// 		{
// 			printf("	\033[1;31mcmd: %s\033[0m←\033[1;32mPIPE\033[0m→\033[1;34mcmd: %s\033[0m\n", root->cmd_left, root->cmd_right);
// 			printf("		↓\n");
// 		}
// 		root = root->left;
// 	}
// }

int	main(void)
{
	char	*input;
	t_ast	*root;

	while (1)
	{
		input = readline(get_prompt());
		if (input == NULL)
			exit(0);
		if (*input)
			add_history(input);
		root = parse(input);
		// print_tree(root);
	}
	return (0);
}
