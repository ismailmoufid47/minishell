#include "../include/shell_bonus.h"

int	wildcard_match(char *pattern, char *file)
{
	char	*last_star;
	char	*last_match;

	last_star = NULL;
	last_match = NULL;
	while (*file)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (1);
			last_star = pattern;
			last_match = file;
		}
		else if (*pattern == *file)
		{
			pattern++;
			file++;
		}
		else if (last_star)
		{
			pattern = last_star;
			file = ++last_match;
		}
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

char	**get_cwd_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				i;

	dir = opendir(".");
	entry = readdir(dir);
	i = 1;
	while (entry)
	{
		i++;
		entry = readdir(dir);
	}
	closedir(dir);
	dir = opendir(".");
	files = malloc(i * sizeof(char *));
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if ((entry->d_name)[0] != '.')
			files[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	files[i] = NULL;
	return ((closedir(dir)), files);
}




t_list	*tokens_to_list(char **tokens)
{
	int		i;
	t_list	*nav;
	t_list	*head;

	if (!tokens || !tokens[0])
		return (NULL);
	head = create_list_node(tokens[0], CMD);
	head->value = ft_strdup(head->value);
	nav = head;
	i = 0;
	while (tokens[++i])
	{
		nav->next = create_list_node(tokens[i], CMD);
		nav->next->value = ft_strdup(nav->next->value);
		nav = nav->next;
	}
	ft_free_split(tokens);
	return (head);
}

void	replace_match(t_list **prev, t_list *current, char **files)
{
	int		i;
	t_list *last;

	last = current->next;
	if (current != *prev)
	{
		free(current->value);
		free(current);
	}
	current = *prev;
	i = 0; 
	while (files[i])
	{
		if (files[i][0])
		{
			current->next = create_list_node(files[i], CMD);
			current->next->value = ft_strdup(current->next->value);
			current = current->next;
		}
		i++;
	}
	current->next = last;
}

char	**list_to_char(t_list *list)
{
	int		count;
	t_list	*current;
	char	**result;

	count = 0;
	current = list;
	while (current)
	{
		count++;
		current = current->next;
	}
	result = malloc((count + 1) * sizeof(char *));
	count = 0;

	while (list)
	{
		result[count] = list->value;
		current = list;
		list = list->next;
		count++;
	}
	result[count] = NULL;
	return (result);
}

char	**match_wild_card(t_list *head)
{
	t_list	*nav;
	t_list	*prev;
	int		j;
	char	**files;

	nav = head;
	prev = head;
	while (nav)
	{
		files = get_cwd_files();
		j = 0;
		while (files[j] && nav->value[0] != '"'
			&& nav->value[0] != '\'' && ft_strchr(nav->value, '*'))
		{
			if (!wildcard_match(nav->value, files[j]))
				files[j][0] = '\0';
			j++;
		}
		if (j)
		{
			replace_match(&prev, nav, files);
			nav =prev->next;

		}
		ft_free_split(files);
		prev = nav;
		nav = nav->next;
	}
	files = list_to_char(head);
	return (free_list(head), files);
}

void	print_files(char **files)
{
	int i = 0;
	while (files[i])
		printf("--> %s\n", files[i++]);
}
int	main(int argc, char **argv)
{
	char **argv2;
	char **res;
	int i = 0;
	argv2 = malloc((argc  +  1) * sizeof(char *));
	while (argv[i])
	{
		argv2[i] = ft_strdup(argv[i]);
		i++;
	}
	argv2[i] = NULL;
	res = match_wild_card(tokens_to_list(argv2));
	print_files(res);
	ft_free_split(res);
}
