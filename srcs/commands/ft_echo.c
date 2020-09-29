/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:58:23 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 11:44:05 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
#include <stdio.h>

//#include "minishell.h"

int		ft_echo(t_all *all)
{
	int		i;
	int		f;

	i = 1;
	f = 1;
	if (!ft_strncmp(all->argv[i], "-n", 3))
	{
		f = 0;
		++i;
	}
	while (all->argv[i])
	{
		ft_putstr_fd(all->argv[i], i);
		++i;
		if (all->argv[i])
			ft_putchar_fd(' ', 1);
	}
	if (f)
		ft_putchar_fd('\n', 1);
	return (errno);
}
