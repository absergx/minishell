/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:43:28 by memilio           #+#    #+#             */
/*   Updated: 2020/10/06 15:32:59 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_error(char *line, int f)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (!f && line)
	{
		ft_putstr_fd(line, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (f == 1)
		ft_putendl_fd("too many arguments", 2);
}

static int	ft_exit_validate_arg(char *line)
{
	int		j;

	j = 0;
	if (*line == '-' || *line == '+')
		line++;
	while (line[j])
	{
		if (!ft_isdigit(line[j]))
			return (0);
		++j;
	}
	return ((j > 0) ? 1 : 0);
}

int			ft_exit(t_all *all)
{
	int		argsize;
	int		valid;

	ft_putendl_fd("exit", 1);
	if ((argsize = ft_strstrlen(all->argv)) == 1)
		exit(g_status);
	if ((valid = ft_exit_validate_arg(all->argv[1])) && argsize > 2)
		ft_exit_error(NULL, 1);
	else if (valid && argsize == 2)
		exit(ft_atoi(all->argv[1]));
	else if (!valid)
	{
		ft_exit_error(all->argv[1], 0);
		exit(255);
	}
	return (errno);
}
