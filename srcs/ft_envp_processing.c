/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:13:16 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 12:27:49 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_envp_value(t_all *all, char *name)
{
	int		i;

	i = 0;
	while (all->envp[i] && ft_strncmp(all->envp[i], name, ft_strlen(name)))
		++i;
	if (all->envp[i] == NULL)
		return (NULL);
	return (ft_strdup(&(all->envp[i][ft_strlen(name) + 1])));
}


