/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:16:21 by memilio           #+#    #+#             */
/*   Updated: 2020/09/27 19:08:36 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_argv(char **argv, int words)
{
	char	**new_argv;
	int		i;

	i = -1;
	if (!(new_argv = (char **)malloc(sizeof(char *) * (words + 2))))
		return (NULL); // call error
	if (words == 0)
	{
		while (++i < 2)
			new_argv[i] = NULL;
		return (new_argv);
	}
	while (++i < words)
		new_argv[i] = argv[i];
	new_argv[i] = NULL;
	new_argv[i + 1] = NULL;
	free(argv);
	return (new_argv);
}

int		ft_add_word(t_all *all, char *line)
{
	if (!(all->argv = ft_add_argv(all->argv, all->parse.word_count)))
		return (0); // Malloc error
	if (!(all->argv[all->parse.word_count] = ft_substr(line, all->parse.word_s,
		(size_t)(all->parse.word_e - all->parse.word_s + 1))))
		return (0); // Malloc error
	all->parse.word_count += 1;
	ft_skip_spaces(line, &all->parse.word_e);
	all->parse.word_s = all->parse.word_e;
	all->parse.word_e -= 1;
	return (1);
}

int		ft_parse(char *line, t_all *all)
{
	int		quotes;

	quotes = 0;
	if (!line)
		return (0);
	while (1)
	{
		if (!line[all->parse.word_e])
		{
			if (all->parse.word_s != all->parse.word_e && !ft_add_word(all, line))
				exit(1);
			break;
		}
		else if (!quotes && (line[all->parse.word_e] == ' ') && !ft_add_word(all, line))
			return (0);
		all->parse.word_e += 1;
	}
	int i = 0;
	while (all->argv[i])
	{
		printf("%s\n", all->argv[i]);
		++i;
	}
	return (1);
}
