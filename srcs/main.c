/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/09/21 20:32:01 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

char	*get_line(void);

int		last_backslashes(char *line)
{
	size_t	len;
	int		count;

	count = 0;
	len = ft_strlen(line);
	while (len >= 0 && line[len - 1] == '\\')
	{
		++count;
		--len;
	}
	return (count % 2);
}

char	*check_backslash(char *line)
{
	
	char	*tmp;
	char	*ret;

	tmp = NULL;
	ret = NULL;
	if (last_backslashes(line))
	{
		line[ft_strlen(line) - 1] = '\0';
		ft_putstr_fd("\\ ", 3);
		tmp = get_line();
		ret = ft_strjoin(line, tmp);
		free(line);
		free(tmp);
		if (last_backslashes(ret))
			return (check_backslash(ret));
	}
	else
		return (line);
	return (ret);
}

char	*get_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(4, &line) < 0)
		ft_putstr_fd("Error\n", 3);
	return (line);
}

int		main(int argc, char **argv, char **envp)
{
	int		status;
	char	*line;
	t_all	all;

	all.envp = envp;
	all.fds[0] = 3;
	all.fds[1] = 4;
	status = 1;
	dup2(0, 3);
	dup2(1, 4);
	while (status)
	{
		ft_putstr_fd("> ", 3);
		line = get_line();
		ft_minishell(line, &all);
		if (!ft_strcmp(line, "exit"))
			status = 0;
	}
	(void)argc;
	(void)argv;
	return (0);
}
