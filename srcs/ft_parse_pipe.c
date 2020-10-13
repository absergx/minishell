/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:05:05 by memilio           #+#    #+#             */
/*   Updated: 2020/10/13 12:57:49 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pipe(t_all *all)
{
	int pid;

	pipe(all->fds);
	pid = fork();
	if (pid == 0)
	{
		if (!all->have_redir)
			dup2(all->fds[1], 1);
		ft_execute(all);
		exit(1);
	}
	else if (pid < 0)
		ft_malloc_error();
	else
	{
		wait(0);
		if (all->have_redir && ((all->have_redir = 0) == 0))
			dup2(4, 1);
		dup2(all->fds[0], 0);
		close(all->fds[1]);
		close(all->fds[0]);
	}
	return (1);
}

static int	ft_execute_or_pipe(t_all *all, int (*func)(t_all *all), char **word,
		char *line)
{
	int i;

	i = 0;
	if (*word)
		ft_add_word_in_argv(all, word);
	func(all);
	ft_new_argv(all);
	++i;
	while (line[i] && line[i] == ' ')
		++i;
	return (i);
}

int			ft_find_pipe_or_exec(t_all *all, char **word, char *line)
{
	int i;

	i = 0;
	if (line[i] == ';')
	{
		i += ft_execute_or_pipe(all, &ft_execute, word, line + i);
		dup2(3, 0);
		dup2(4, 1);
	}
	else if (line[i] == '|')
	{
		i += ft_execute_or_pipe(all, &ft_pipe, word, line + i);
	}
	return (i);
}
