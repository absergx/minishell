/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 18:53:17 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(3, &line) < 0)
		ft_putstr_fd("Error\n", 2);
	return (line);
}

int		main(int argc, char **argv, char **envp)
{
	int		status;
	char	*line;
	t_all	all;
	int		i;

	all.envp = (char **)malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	i = -1;
	while (envp[++i])
		all.envp[i] = ft_strdup(envp[i]);
	all.envp[i] = NULL;
	status = 1;
	dup2(0, 3);
	dup2(1, 4);
	while (status)
	{
		ft_putstr_fd("> ", 1);
		if (!(line = get_line()))
			continue ;
		all.parse.word_s = 0;
		if (!(all.argv = ft_calloc(2, sizeof(char *))))
			return (0);
		all.size_argv = 2;
		all.parse.word_e = 0;
		all.parse.word_count = 0;
		all.parse.quotes = 0;
		all.parse.space_before = 0;
		ft_parse(line, &all);
		// ft_minishell(line, &all);
		dup2(3, 0);
		dup2(4, 1);
		if (!ft_strcmp(line, "exit"))
			status = 0;
	}
	(void)argc;
	(void)argv;
	return (0);
}
