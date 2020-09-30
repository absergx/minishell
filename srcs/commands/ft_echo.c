/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:58:23 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 13:31:16 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
