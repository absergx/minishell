/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:50:11 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 15:21:32 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/minishell.h"

static int	ft_export_print(t_all *all)
{
	int		i;
	int		j;
	char	*pntr;

	while (all->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(all->envp[i], '='))
		{
			j = -1;
			while (all->envp[i][++j - 1] != '=')
				ft_putchar_fd(all->envp[i][j], 1);
			ft_putchar_fd("\"", 1);
			ft_putstr_fd(&(all->envp[i][j + 1]), 1);
			ft_putchar_fd("\"", 1);
			++i;
		}
		else
			ft_putstr_fd(all->envp[i], 1);
		ft_putchar_fd('\n');
		++i;
	}
	return (errno);
}

int			ft_export_check_name(char *name)
{
	int		i;
	int		f;

	i = 0;
	f = 0;
	while (name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]))
			f = 1;
		else if (ft_isdigit(name[i]) && !f)
			return (0);
		else
			return (0);
		++i;
	}
	return ((i == 0) ? 0 : 1);
}

static void	ft_export_error(t_all *all, char *name)
{
	// STATUS
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int			ft_export(t_all *all)
{
	int		i;

	i = 1;
	if (all->parse.word_count == 1)
		return (ft_export_print(all));
	while (all->argv[i])
	{
		if (!ft_export_check_name(all->argv[i]))
			ft_export_error(all, all->argv[i]);
		else
		{
			
		}
	}
}
