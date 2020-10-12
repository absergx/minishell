/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 13:03:33 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_line(int fd)
{
	char	*line;
	char	buf[2];
	char	*tmp;

	buf[1] = 0;
	line = NULL;
	while (1)
	{
		tmp = line;
		if (read(fd, buf, 1) == 0)
		{
			if (!tmp)
				break ;
			continue ;
		}
		if (!(line = ft_strjoin((line ? line : ""), (*buf == '\n' ? "" : buf))))
			ft_malloc_error();
		if (tmp)
			free(tmp);
		if (*buf == '\n')
			break ;
	}
	return (line);
}

int			ft_clone_envp(char **envp, t_all *all)
{
	int		i;

	if (!(all->envp = (char **)malloc(sizeof(char *)
		* (ft_strstrlen(envp) + 1))))
		ft_malloc_error();
	i = -1;
	while (envp[++i])
		if (!(all->envp[i] = ft_strdup(envp[i])))
			ft_malloc_error();
	all->envp[i] = NULL;
	return (1);
}

void		ft_promt(void)
{
	char	*path;

	path = NULL;
	if ((path = getcwd(NULL, 0)))
	{
		ft_putstr_fd(GREEN"minishell: ~", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("> "ENDCOLOR, 1);
		free(path);
	}
}

static void	ft_minishell(t_all *all)
{
	char *line;

	while (1)
	{
		ft_promt();
		if (!(line = get_line(0)))
			ft_eof();
		if (!ft_strlen(line))
			continue ;
		all->fds[0] = 0;
		all->fds[1] = 1;
		if (!(all->argv = ft_calloc(2, sizeof(char *))))
			ft_malloc_error();
		all->size_argv = 2;
		all->word_count = 0;
		all->have_redir = 0;
		ft_parse(line, all);
		dup2(3, 0);
		dup2(4, 1);
		free(line);
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_all	all;

	g_status = 0;
	ft_clone_envp(envp, &all);
	dup2(0, 3);
	dup2(1, 4);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_quit);
	ft_minishell(&all);
	(void)argc;
	(void)argv;
	return (0);
}
