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

void	ft_do_it(t_commas *el, t_all *all)
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
	execve(el->argv[0], el->argv, all->envp);
}

int		ft_get_argv(t_all *all, char *str, int start, int last)
{
	char *temp = ft_substr(str, start, last - start);
	char **argv = ft_split(temp, ' '); // пробел в КОВЫЧКАХ
//	ft_add_back(&(all->com), argv);
	t_commas *l;

	l = ft_new_commas(argv);

	// Если есть пайп?
	if (all->_pipe)
	{
		pipe(all->fds);
		int pid = fork();
		wait(0);
		if (pid == 0)
		{
			dup2(1, all->fds[0]);
			ft_do_it(l, all);
			close(all->fds[1]);
			close(all->fds[0]);
			exit(0);
		}
		else
		{
			dup2(0, all->fds[1]);
			close(all->fds[0]);
			wait(0);
			close(all->fds[1]);
		}
	}
	else
	{
		int pid;
		pid = fork();
		wait(0);
		if (pid == 0)
			ft_do_it(l, all);
	}
	(void)all;
	(void)argv;
	return (1);
}