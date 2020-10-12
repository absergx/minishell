/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:50:11 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 12:10:32 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_print(t_all *all)
{
	int		i;
	int		j;

	i = -1;
	while (all->envp[++i])
	{
		if (ft_strlen(all->envp[i]) == 0)
			continue ;
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(all->envp[i], '='))
		{
			j = 0;
			while (all->envp[i][j - 1] != '=')
				ft_putchar_fd(all->envp[i][j++], 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(&(all->envp[i][j]), 1);
			ft_putchar_fd('"', 1);
		}
		else
			ft_putstr_fd(all->envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (errno);
}

static int	ft_export_check_name(char *name)
{
	int		i;
	int		f;

	i = 0;
	f = 0;
	while (name[i] && name[i] != '=')
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

static void	ft_export_error(char *name)
{
	g_status = 1;
	ft_putstr_fd(RED"minishell: export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n"ENDCOLOR, 2);
}

static int	ft_export_add_new(t_all *all, char *new_line)
{
	char	**new_envp;
	int		size;
	int		i;

	size = ft_strstrlen(all->envp);
	if (!(new_envp = (char **)malloc(sizeof(char *) * (size + 2))))
		ft_malloc_error();
	i = -1;
	while (all->envp[++i])
		new_envp[i] = all->envp[i];
	if (!(new_envp[i] = ft_strdup(new_line)))
		ft_malloc_error();
	new_envp[i + 1] = NULL;
	free(all->envp);
	all->envp = new_envp;
	return (1);
}

int			ft_export(t_all *all)
{
	int		i;
	int		j;

	i = 0;
	if (ft_strstrlen(all->argv) == 1)
		return (ft_export_print(all));
	while (all->argv[++i])
	{
		if (!ft_export_check_name(all->argv[i]))
			ft_export_error(all->argv[i]);
		else
		{
			if (((j = ft_get_envp_key(all, all->argv[i])) != -1)
				&& (ft_strchr(all->argv[i], '=')))
			{
				free(all->envp[j]);
				if (!(all->envp[j] = ft_strdup(all->argv[i])))
					ft_malloc_error();
			}
			else if (j == -1)
				ft_export_add_new(all, all->argv[i]);
		}
	}
	return (errno);
}
