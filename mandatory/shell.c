#include "include/shell.h"

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
	print_list(list, 1);
	root = create_ast(list);
	return (root);
}

void	print_tree(t_ast *root)
{
	printf("\n		TREE\n\n");
	while (root)
	{
		if (root->type == PIPE)
		{
			printf("	\033[1;31mcmd: %s\033[0m←\033[1;32mPIPE\033[0m→\033[1;34mcmd: %s\033[0m\n", root->left->cmd, root->right->cmd);
			printf("		↓\n");
		}
		root = root->left;
	}
}

int	main(void)
{
	char	*input;
	t_ast	*root;
	int		history_fd;

	history_fd = open_wraper("command_history",
			O_RDWR | O_CREAT | O_APPEND, 0666);
	load_history("command_history.txt");
	while (1)
	{
		input = readline(get_prompt());
		if (input == NULL)
			exit(0);
		if (*input)
		{
			add_history(input);
			write(history_fd, input, strlen(input));
			write(history_fd, "\n", 1);
		}
		root = parse(input);
		(void)root;
		// print_tree(root);
		free(input);
	}

	close(history_fd);
	return (0);
}
