/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/09/27 17:09:48 by memilio          ###   ########.fr       */
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

	all.envp = envp;
	status = 1;
	dup2(0, 3);
	dup2(1, 4);
	while (status)
	{
		ft_putstr_fd("> ", 1);
		if (!(line = get_line()))
			continue ;
		all.parse.word_s = 0;
		all.parse.word_e = 0;
		all.parse.word_count = 0;
		ft_parse(line, &all);
		// ft_minishell(line, &all);
		// dup2(3, 0);
		// dup2(4, 1);
		if (!ft_strcmp(line, "exit"))
			status = 0;
	}
	(void)argc;
	(void)argv;
	return (0);
}
