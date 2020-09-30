/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:13:16 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 19:07:59 by memilio          ###   ########.fr       */
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

char	*ft_get_key_from_envp(char *line)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_strchr(line, '='))
		return (NULL);
	while (line[i] != '=')
		++i;
	if (!(key = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (line[i] != '=')
	{
		key[i] = line[i];
		++i;
	}
	key[i] = '\0';
	return (key);
}

int		ft_get_envp_key(t_all *all, char *name)
{
	size_t	i;
	size_t	len;
	char	*key;

	i = 0;
	if ((key = ft_get_key_from_envp(name)))
		name = key;
	len = ft_strlen(name);
	while (all->envp[i])
	{
		if (!ft_strncmp(all->envp[i], name, len)
			&& (all->envp[i][len] == '=' || !all->envp[i][len]))
			break ;
		++i;
	}
	if (key)
		free(key);
	if (all->envp[i] == NULL)
		return (-1);
	return ((int)i);
}
