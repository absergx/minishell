/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/10/08 18:30:14 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(int fd)
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
			// ft_putstr_fd(" \b\b", fd);
			continue ;
		}
		line = ft_strjoin((line ? line : ""), (*buf == '\n' ? "" : buf));
		if (tmp)
			free(tmp);
		if (*buf == '\n')
			break ;
	}
	return (line);
}

int		ft_clone_envp(char **envp, t_all *all)
{
	int		i;

	if (!(all->envp = (char **)malloc(sizeof(char *)
		* (ft_strstrlen(envp) + 1))))
		return (0);
	i = -1;
	while (envp[++i])
		if (!(all->envp[i] = ft_strdup(envp[i])))
			return (0);
	all->envp[i] = NULL;
	return (1);
}

void	ft_promt(void)
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

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_all	all;

	g_status = 0;
	if (!ft_clone_envp(envp, &all))
		exit(0); // ERROR
	dup2(0, 3);
	dup2(1, 4);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_quit);
	while (1)
	{
		ft_promt();
		if (!(line = get_line(0)))
			ft_eof();
		if (!ft_strlen(line))
			continue ;
		all.parse.word_s = 0;
		all.fds[0] = 0;
		all.fds[1] = 1;
		if (!(all.argv = ft_calloc(2, sizeof(char *))))
			return (0);
		all.size_argv = 2;
		all.parse.word_e = 0;
		all.parse.word_count = 0;
		all.parse.space_before = 0;
		ft_parse(line, &all);
		// ft_minishell(line, &all);
		dup2(3, 0);
		dup2(4, 1);
		free(line);
	}
	(void)argc;
	(void)argv;
	return (0);
}
