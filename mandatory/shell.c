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
	print_list(list, 1);
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

void	load_history(const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open history file");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(void)
{
	char	*input;
	t_ast	*root;
	int		history_fd;

	history_fd = open("command_history.txt",
			O_WRONLY | O_CREAT | O_APPEND | O_CREAT, 0600);
	load_history("command_history.txt");
	if (history_fd == -1)
		error("Failed to open history file");
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
