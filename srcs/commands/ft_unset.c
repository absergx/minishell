/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:03:35 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 18:18:45 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_unset(t_all *all)
{
	int		i;
	int		j;

	i = 1;
	while (all->argv[i])
	{
		if ((j = ft_get_envp_key(all, all->argv[i])) != -1)
		{
			free(all->envp[j]);
			all->envp[j] = ft_strdup("");
		}
		++i;
	}
	return (errno);
}
