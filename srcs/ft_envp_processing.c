/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:13:16 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 17:07:15 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_envp_value(t_all *all, char *name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (all->envp[i])
	{
		if (!ft_strncmp(all->envp[i], name, len)
			&& (all->envp[i][len] == '=' || !all->envp[i][len]))
			break ;
		++i;
	}
	if (all->envp[i] == NULL)
		return (NULL);
	return (ft_strdup(&(all->envp[i][ft_strlen(name) + 1])));
}

int		ft_get_envp_key(t_all *all, char *name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (all->envp[i])
	{
		if (!ft_strncmp(all->envp[i], name, len)
			&& (all->envp[i][len] == '=' || !all->envp[i][len]))
			break ;
		++i;
	}
	if (all->envp[i] == NULL)
		return (-1);
	return ((int)i);
}
