/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:26:53 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 19:41:12 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_realloc_argv(t_all *all)
{
	char	**new_argv;
	int		i;

	if (!(new_argv = ft_calloc(all->size_argv * 2, sizeof(char *))))
		ft_malloc_error();
	i = 0;
	all->size_argv *= 2;
	while (all->argv[i])
	{
		if (!(new_argv[i] = ft_strdup(all->argv[i])))
			ft_malloc_error();
		free(all->argv[i]);
		++i;
	}
	free(all->argv);
	all->argv = new_argv;
	return (1);
}

int			strstrfree(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		++i;
	}
	free(str);
	return (1);
}

int			skip_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == ' ')
		++i;
	return (i);
}

int			ft_add_word_in_argv(t_all *all, char **word)
{
	if (!(all->argv[all->word_count] = ft_strdup(*word)))
		ft_malloc_error();
	free(*word);
	*word = 0;
	all->word_count += 1;
	if (all->word_count == all->size_argv - 1)
		ft_realloc_argv(all);
	return (1);
}

int			ft_new_argv(t_all *all)
{
	strstrfree(all->argv);
	if (!(all->argv = ft_calloc(2, sizeof(char *))))
		ft_malloc_error();
	all->size_argv = 2;
	all->word_count = 0;
	return (1);
}
