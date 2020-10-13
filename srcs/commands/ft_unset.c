/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:03:35 by memilio           #+#    #+#             */
/*   Updated: 2020/10/13 13:59:06 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_check_name(char *name)
{
	int		i;
	int		f;

	i = 0;
	f = 0;
	while (name[i])
	{
		if (ft_isalpha(name[i]) || name[i] == '_')
		{
			f = 1;
			++i;
		}
		else if (ft_isdigit(name[i]) && f)
			++i;
		else
			return (0);
	}
	return ((i == 0) ? 0 : 1);
}

static void	ft_unset_error(char *name)
{
	ft_putstr_fd(RED"minishell: unset: '", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier"ENDCOLOR, 2);
}

int			ft_unset(t_all *all)
{
	int		i;
	int		j;

	i = 1;
	while (all->argv[i])
	{
		if (!ft_unset_check_name(all->argv[i]))
			ft_unset_error(all->argv[i]);
		else
		{
			if ((j = ft_get_envp_key(all, all->argv[i])) != -1)
			{
				free(all->envp[j]);
				if (!(all->envp[j] = ft_strdup("")))
					ft_malloc_error();
			}
		}
		++i;
	}
	return (errno);
}
