/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:00:33 by memilio           #+#    #+#             */
/*   Updated: 2020/10/13 12:57:46 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execute_our(t_all *all)
{
	if (!ft_strcmp(all->argv[0], "cd"))
		return (ft_cd(all));
	else if (!ft_strcmp(all->argv[0], "echo"))
		return (ft_echo(all));
	else if (!ft_strcmp(all->argv[0], "env"))
		return (ft_env(all));
	else if (!ft_strcmp(all->argv[0], "export"))
		return (ft_export(all));
	else if (!ft_strcmp(all->argv[0], "pwd"))
		return (ft_pwd(all));
	else if (!ft_strcmp(all->argv[0], "unset"))
		return (ft_unset(all));
	return (-1);
}

static void	ft_get_path(t_all *all)
{
	int i;

	i = 0;
	if ((all->execute.is_relative = ft_not_absolute_path(all)))
		while (all->execute.path[i])
		{
			if (!(all->execute.temp2 = ft_strjoin(all->execute.path[i], "/")))
				ft_malloc_error();
			if (!(all->execute.temp = ft_strjoin(all->execute.temp2,
			all->argv[0])))
				ft_malloc_error();
			if ((all->execute.fd = open(all->execute.temp, O_RDONLY)) > 0)
			{
				all->execute.res = all->execute.temp;
				free(all->execute.temp2);
				break ;
			}
			free(all->execute.temp);
			free(all->execute.temp2);
			++i;
		}
	if (!(all->execute.res))
		if (!(all->execute.res = ft_strdup(all->argv[0])))
			ft_malloc_error();
	strstrfree(all->execute.path);
}

static int	ft_execute_fork(t_all *all)
{
	int		pid;

	pid = fork();
	if (pid == 0)
		exit(execve(all->execute.res, all->argv, all->envp));
	else if (pid < 0)
		ft_malloc_error();
	else
	{
		wait(&(all->execute.status));
		check_exit_status(all->execute.status);
		if (all->execute.res)
			free(all->execute.res);
	}
	return (1);
}

static int	ft_send_error(t_all *all, struct stat *buf, int t)
{
	g_status = S_ISDIR(buf->st_mode) ? 126 : 127;
	if (all->execute.is_relative)
		errno = 0;
	else if (t < 0)
		errno = 2;
	else if ((S_IXUSR & buf->st_mode) == 0)
	{
		errno = 13;
		g_status = 1;
	}
	if (g_status == 126)
		ft_error(all->argv, 21);
	else
		ft_error(all->argv, errno);
	strstrfree(all->argv);
	return (1);
}

int			ft_execute(t_all *all)
{
	int				i;
	struct stat		buf;
	int				st;

	if (all->argv[0] == 0)
		return (1);
	if (!ft_strcmp(all->argv[0], "exit"))
		return (ft_exit(all));
	errno = 0;
	g_status = 0;
	if ((i = ft_execute_our(all)) != -1)
	{
		if (errno)
			ft_error(all->argv, errno);
		return (i);
	}
	ft_get_path_in_argv(all);
	ft_get_path(all);
	st = stat(all->execute.res, &buf);
	if (st < 0 || S_ISDIR(buf.st_mode) || !(S_IXUSR & buf.st_mode))
		return (ft_send_error(all, &buf, st));
	return (ft_execute_fork(all));
}
