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

t_ast	*create_redirection_node(char *file)
{
	t_ast *red;

	red = malloc(sizeof(t_ast)); 
	red->file = file;
	red->type = IN;
	return (red);
}

//t_ast *creat_ast(char **tokens)
//{
//	t_ast	*root;
//	t_ast	*pipe;
//	t_ast	*red;
//
//	int i = 0;
//	while (tokens[i])
//	{
//		if (!ft_strcmp(tokens[i], "<"))
//		{
//			red = create_redirection_node(tokens[i + 1]);
//			if (i == 0)
//
//		}
//	}
//}

t_ast	*parse(char *cmd_line)
{
	char	**tokens;
	t_ast	*root;

	root = NULL;
	cmd_line = expand_env_variable(cmd_line);
	tokens = tokenize(cmd_line);
	print_tokens(tokens);
//	root = create_ast(tokens);
	return (root);
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
		//print_tree(parse(input));
	}
	return (0);
}


        