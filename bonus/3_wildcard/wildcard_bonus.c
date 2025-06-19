#include "../include/shell_bonus.h"

int	wildcard_match(char *pattern, char *file)
{
	char	*last_star;
	char	*last_match;

	last_match = ((last_star = NULL), NULL);
	while (*file)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (!*pattern)
				return (1);
			last_match = ((last_star = pattern), file);
		}
		else if (*pattern == *file)
			file = ((pattern++), file + 1);
		else if (last_star)
			file = ((pattern = last_star), ++last_match);
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

char	**get_cwd_files(int show_hidden)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				count;

	dir = opendir(".");
	entry = readdir(dir);
	count = 1;
	while (entry)
		entry = ((count++), readdir(dir));
	closedir(dir);
	dir = opendir(".");
	files = malloc(count * sizeof(char *));
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if ((entry->d_name)[0] != '.' || show_hidden)
			files[count++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	files[count] = NULL;
	return ((closedir(dir)), files);
}

t_list	*get_matchs(char **files)
{
	int		i;
	t_list	*head;
	t_list	*current;

	head = ((i = -1), (current = NULL), NULL);
	while (files[++i])
	{
		if (files[i][0])
		{
			if (!head)
			{
				head = create_list_node(files[i], CMD);
				head->value = ft_strdup(head->value);
				current = head;
			}
			else
			{
				current->next = create_list_node(files[i], CMD);
				current->next->value = ft_strdup(current->next->value);
				current = current->next;
			}
		}
	}
	return (head);
}

char	**match_wild_card(t_list *head)
{
	t_list	*nav;
	t_list	*prev;
	int		j;
	char	**files;

	nav = head;
	prev = NULL;
	while (nav)
	{
		files = get_cwd_files(nav->value[0] == '.');
		j = 0;
		while (files[j] && nav->value[0] != '"'
			&& nav->value[0] != '\'' && ft_strchr(nav->value, '*'))
		{
			if (!wildcard_match(nav->value, files[j]))
				files[j][0] = '\0';
			j++;
		}
		if (j)
			head = link_matchs(head, &prev, &nav, get_matchs(files));
		ft_free_split(files);
		nav = ((prev = nav), nav->next);
	}
	files = list_to_char(head);
	return (free_list(head), files);
}
