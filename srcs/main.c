/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/09/17 19:22:43 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

char	*get_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(0, &line) < 0)
		ft_putstr_fd("Error\n", 0);
	return (line);
}

int		main(void)
{
	int		status;
	char	*line;

	status = 1;
	while (status)
	{
		ft_putstr_fd("> ", 0);
		line = get_line();
		if (!ft_strcmp(line, "exit"))
			status = 0;
		else
			ft_putendl_fd(line, 0);
	}
	return (0);
}
