/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:33:41 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 16:38:30 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_fd(char *redir, char **word)
{
	int fd;

	fd = 0;
	if (!ft_strcmp("right", redir))
		fd = open(*word, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (!ft_strcmp("left", redir))
		fd = open(*word, O_RDONLY);
	else
		fd = open(*word, O_CREAT | O_APPEND | O_WRONLY, 0644);
	return (fd);
}

int		ft_err_fd(t_all *all, char **word, char *line)
{
	int			fd;
	struct stat	buf;

	errno = stat(*word, &buf) < 0 ? 2 : 13;
	ft_add_word_in_argv(all, word);
	ft_error(all->argv, errno);
	fd = 0;
	while (line[fd] && (line[fd] != '|' || line[fd] != ';'))
		++fd;
	ft_new_argv(all);
	free(*word);
	*word = 0;
	return (fd);
}

int		ft_create_file(t_all *all, char **word, char *line, char *redir)
{
	int fd;

	fd = ft_get_fd(redir, word);
	if (fd < 0)
		return (ft_err_fd(all, word, line));
	else if (!ft_strcmp("left", redir))
	{
		all->fds[0] = fd;
		dup2(all->fds[0], 0);
	}
	else
	{
		all->fds[1] = fd;
		dup2(all->fds[1], 1);
	}
	free(*word);
	*word = 0;
	return (0);
}

int		ft_parse_file_name(t_all *all, char *line, int *i, char *redir)
{
	char *word;

	word = 0;
	while (1)
	{
		if (ft_strchr("| ;><", line[*i]) || line[*i] == 0)
		{
			if (word)
				*i += ft_create_file(all, &word, line, redir);
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
