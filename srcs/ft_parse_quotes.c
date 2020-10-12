/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:59:26 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 18:36:23 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_double_quote(char *line, char **word, t_all *all)
{
	int i;

	i = 1;
	if (line[i] == '"')
	{
		*word = ft_add_symbol(*word, 0);
		return (2);
	}
	while (line[i] != '"' && line[i])
	{
		if (line[i] == '\\' && ft_strchr("$\"\\", line[i + 1]))
			++i;
		else if (line[i] == '$')
		{
			ft_env_res(line, &i, all, word);
			if (line[i] == '"')
			{
				*word = ft_add_symbol(*word, 0);
				break ;
			}
		}
		*word = ft_add_symbol(*word, line[i]);
		++i;
	}
	return (i + 1);
}

static int	ft_single_quote(char *line, char **word)
{
	int i;

	i = 1;
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

int			ft_quotes(t_all *all, char *line, char **word)
{
	int i;

	i = 0;
	if (line[i] == '\'')
	{
		i += ft_single_quote(line + i, word);
	}
	else
	{
		i += ft_double_quote(line + i, word, all);
	}
	return (i);
}
