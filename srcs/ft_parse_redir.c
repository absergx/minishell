/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:55:26 by memilio           #+#    #+#             */
/*   Updated: 2020/10/13 15:12:11 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_file_name(t_all *all, char *line, int *i, char *redir)
{
	char	*word;
	int		temp;

	word = 0;
	while (1)
	{
		if (ft_strchr("| ;><", line[*i]) || line[*i] == 0)
		{
			if (word)
				*i = ((temp = ft_create_file(all, &word, line, redir)) > 0)
					? temp : *i;
			if (line[*i] == ' ')
				*i += 1;
			break ;
		}
		else
		{
			word = ft_add_symbol(word, line[*i]);
			*i += 1;
		}
	}
	free(word);
	return (0);
}

static int	error_redir(char *line, char c, t_all *all)
{
	int i;

	i = 0;
	g_status = 258;
	ft_putstr_fd(RED"minishell: syntax error near unexpected token ", 2);
	if (c == '>')
		ft_putstr_fd("'>'", 2);
	else if (c == '<')
		ft_putstr_fd("'<'", 2);
	else if (c == '|')
		ft_putstr_fd("'|'", 2);
	else
		ft_putstr_fd("';'", 2);
	ft_putendl_fd(ENDCOLOR, 2);
	while (line[i])
		++i;
	ft_new_argv(all);
	return (i);
}

static int	ft_redir(t_all *all, char *line, char *redir)
{
	int i;

	i = 1;
	if (line[i] == '>' && line[0] != '<')
	{
		i = 2;
		redir = "double_redir";
	}
	while (line[i] && line[i] == ' ')
		++i;
	if (ft_strchr("<>|;", line[i]) || !line[i])
	{
		if (!line[i])
			i += error_redir(line, line[0], all);
		else
			i += error_redir(line, line[i], all);
	}
	else
		ft_parse_file_name(all, line, &i, redir);
	return (i);
}

int			ft_redir_left_or_right(t_all *all, char *line, char **word,
			char *redir)
{
	int i;

	i = 0;
	all->have_redir = 1;
	if (*word)
		ft_add_word_in_argv(all, word);
	i += ft_redir(all, line, redir);
	return (i);
}
