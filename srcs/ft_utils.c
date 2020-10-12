/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:13:16 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 16:25:18 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_envp_value(t_all *all, char *name)
{
	size_t	i;
	size_t	len;
	char	*res;

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
	if (!(res = ft_strdup(&(all->envp[i][ft_strlen(name) + 1]))))
		ft_malloc_error();
	return (res);
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
		ft_malloc_error();
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

void	ft_get_path_in_argv(t_all *all)
{
	all->execute.fd = 0;
	all->execute.temp = ft_get_envp_value(all, "PATH");
	if (!(all->execute.temp))
		if (!(all->execute.temp = ft_strdup("")))
			ft_malloc_error();
	if (!(all->execute.path = ft_split(all->execute.temp, ':')))
		ft_malloc_error();
	free(all->execute.temp);
	all->execute.res = NULL;
}

int		ft_not_absolute_path(t_all *all)
{
	if (all->argv[0] && ft_strchr("./", all->argv[0][0]))
		return (0);
	return (1);
}
