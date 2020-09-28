#include "minishell.h"


void	print_argv(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("%d - %s\n", i, argv[i]);
		++i;
	}
}

int 	ft_realloc_argv(t_all *all)
{
	char	**new_argv;
	int		i;

	new_argv = ft_calloc(all->size_argv * 2, sizeof(char *));
	i = 0;
	all->size_argv *= 2;
	while (all->argv[i])
	{
		new_argv[i] = ft_strdup(all->argv[i]);
		free(all->argv[i]);
		++i;
	}
	free(all->argv);
	all->argv = new_argv;
	return (1);
}

int 	ft_add_word(t_all *all, char *line, char *word)
{
	word = ft_substr(line, all->parse.word_s, all->parse.word_e - all->parse.word_s + 1);
	all->argv[all->parse.word_count] = word;
	all->parse.word_count += 1;
	if (all->parse.word_count == all->size_argv - 1)
		ft_realloc_argv(all);
	return (1);
}

char 	*ft_add_symbol(char *word, char c)
{
	char	*new_word;
	size_t	i;

	i = 0;
	new_word = 0;
	if (!word)
	{
		word = ft_calloc(1, 2);
		word[0] = c;
		return (word);
	}
	else
	{
		new_word = ft_calloc(ft_strlen(word) + 2, 1);
		while (i < ft_strlen(word))
		{
			new_word[i] = word[i];
			++i;
		}
		new_word[i] = c;
		return (new_word);
	}
}

int 	ft_single_quote(char *line, char **word)
{
	int i = 1;
	if (line[i] == '\'')
	{
		*word = ft_add_symbol(*word, 0);
		return (2);
	}
	while (line[i] != '\'' && line[i])
	{
		*word = ft_add_symbol(*word, line[i]);
		++i;
	}
	++i;
	return (i);
}

int 	ft_double_quote(char *line, char **word)
{
	int i = 1;
//	char *temp;

	if (line[i] == '"')
	{
		*word = ft_add_symbol(*word, 0);
		return (2);
	}
	// ($"\)/
	while (line[i] != '"' && line[i])
	{
		if (line[i] == '\\' && ft_strchr("$\"\\", line[i + 1]))
			++i;
		else if (line[i] == '$')
			++i; // добавить замену переменных
		*word = ft_add_symbol(*word, line[i]);
		++i;
	}
	++i;
	return (i);
}

int		ft_parse(char *line, t_all *all)
{
	char	*word;
	char	*temp;
	int		i;

	word = NULL;
	i = 0;
	if (!line)
		return (0);
	temp = ft_strtrim(line, " ");
	free(line);
	line = temp;
	while (1)
	{
		if (line[i] == 0)
		{
			if (word)
				all->argv[all->parse.word_count] = word;
			break;
		}
		if (line[i] == '\'')
		{
			i += ft_single_quote(line + i, &word);
		}
		else if (line[i] == '"')
		{
			i += ft_double_quote(line + i, &word);
		}
		else if (line[i] == ' ' || line[i + 1] == 0)
		{
			if (line[i + 1] == 0)
			{
				word = ft_add_symbol(word, line[i]);
			}
			all->argv[all->parse.word_count] = word;
			word = 0;
			all->parse.word_count += 1;
			if (all->parse.word_count == all->size_argv - 1)
				ft_realloc_argv(all);
			++i;
		}
		else
		{
			word = ft_add_symbol(word, line[i]);
			++i;
		}
	}
	print_argv(all->argv);
	return (1);
}