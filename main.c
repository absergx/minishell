/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/09/17 17:30:04 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

char	*get_line(void)
{
	char	*line;

}

int		main(int argc, char **argv, char **envp)
{
	int		status;
	char	*line;

	status = 1;
	while (status)
	{
		ft_putchar_fd("> ", 0);
		line = get_line();
	}
	return (0);
}
