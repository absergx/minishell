/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:07:27 by casubmar          #+#    #+#             */
/*   Updated: 2020/10/12 18:15:38 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_add_symbol(char *word, char c)
{
	char	*new_word;
	size_t	i;

	i = 0;
	new_word = 0;
	if (!word)
	{
		if (!(word = ft_calloc(1, 2)))
			ft_malloc_error();
		word[0] = c;
		return (word);
	}
	else
	{
		if (!(new_word = ft_calloc(ft_strlen(word) + 2, 1)))
			ft_malloc_error();
		while (i < ft_strlen(word))
		{
			new_word[i] = word[i];
			++i;
		}
		new_word[i] = c;
		free(word);
		return (new_word);
	}
}

static int	ft_check_symbol(t_all *all, char *line, char **word)
{
	int		i;

	i = 0;
	if (line[i] == ' ')
	{
		if ((*word))
			ft_add_word_in_argv(all, word);
		while (line[i] && line[i] == ' ')
			++i;
	}
	else if (line[i] == '\\')
	{
		*word = ft_add_symbol(*word, line[i + 1]);
		i += 2;
	}
	else if (line[i] == ';' || line[i] == '|')
		i += ft_find_pipe_or_exec(all, word, line + i);
	else if (line[i] == '>')
		i += ft_redir_left_or_right(all, line + i, word, "right");
	else if (line[i] == '<')
		i += ft_redir_left_or_right(all, line + i, word, "left");
	return (i);
}

static int	check_valid_start(char *str)
{
	int i;

	i = skip_spaces(str);
	if (str[i] == '|')
		ft_putstr_fd(RED"minishell: syntax error near \
unexpected token '|'\n"ENDCOLOR, 2);
	else if (str[i] == ';')
		ft_putstr_fd(RED"minishell: syntax error near \
unexpected token ';'\n"ENDCOLOR, 2);
	if (str[i] == '|' || str[i] == ';')
	{
		g_status = 258;
		while (str[i])
			++i;
	}
	return (i);
}

static void	ft_end_parse(t_all *all, char **word)
{
	if (*word)
		ft_add_word_in_argv(all, word);
	ft_execute(all);
	strstrfree(all->argv);
}

int			ft_parse(char *line, t_all *all)
{
	char	*word;
	int		i;

	word = NULL;
	i = check_valid_start(line);
	while (1)
	{
		if (line[i] == 0)
		{
			ft_end_parse(all, &word);
			break ;
		}
		if (line[i] == '\'' || line[i] == '"')
			i += ft_quotes(all, line + i, &word);
		else if (ft_strchr(" \\<>;|", line[i]))
			i += ft_check_symbol(all, line + i, &word);
		else if (line[i] == '$')
			ft_env_res(line, &i, all, &word);
		else
		{
			word = ft_add_symbol(word, line[i]);
			++i;
		}
	}
	return (1);
}
