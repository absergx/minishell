/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:46:16 by casubmar          #+#    #+#             */
/*   Updated: 2020/09/22 17:46:17 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_do_it(t_commas *el, t_all *all)
{
	int fd;
	char *path = NULL;
	int i = 0;
	char *res;

	while (all->envp[i])
	{
		if (!ft_strncmp("PATH", all->envp[i], 4))
		{
			path = all->envp[i];
			break;
		}
		++i;
	}

	char **paths_args = ft_split(path + 5, ':');
	i = 0;
	while (paths_args[i])
	{
		res = ft_strjoin(paths_args[i], "/");
		res = ft_strjoin(res, el->argv[0]);
		if ((fd = open(res, O_RDONLY)) > 0)
			break;
		free(res);
		++i;
	}
	free(el->argv[0]);
	el->argv[0] = res;
	return (execve(el->argv[0], el->argv, all->envp));
}

int		ft_get_argv(t_all *all, char *str, int start, int last)
{
	char *temp = ft_substr(str, start, last - start);
	char **argv = ft_split(temp, ' '); // пробел в КОВЫЧКАХ
	t_commas *l;

	l = ft_new_commas(argv);
	all->fds[0] = 3;
	all->fds[1] = 4;
	// Если есть пайп?
	if (all->_pipe)
	{
		pipe(all->fds);
		int pid = fork();
		if (pid == 0)
		{
			dup2(all->fds[1], 1);
			close(all->fds[1]);
			ft_do_it(l, all);
			close(all->fds[0]);
			exit(0);
		}
		else
		{
			dup2(all->fds[0], 0);
			close(all->fds[1]);
			wait(0);
			close(all->fds[0]);
		}
	}
	else
	{
		int pid;
		pid = fork();
		if (pid == 0)
			exit(ft_do_it(l, all));
		else
			wait(0);
	}
	return (1);
}