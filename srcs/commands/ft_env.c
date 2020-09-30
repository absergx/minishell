/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:47:23 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 13:40:22 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_all *all)
{
	int		i;

	i = 0;
	while (all->envp[i])
	{
		if (ft_strchr(all->envp[i], '='))
			ft_putendl_fd(all->envp[i], 1);
		++i;
	}
	return (errno);
}
