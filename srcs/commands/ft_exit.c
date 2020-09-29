/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:43:28 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 19:55:07 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_error(char *line, int f)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 1);
	if (!f && line)
	{
		ft_putstr_fd(line, 1);
		ft_putendl_fd(": numeric argument required", 1);
	}
	else if (f == 1)
		ft_putendl_fd("too many arguments", 1);
}

int		ft_exit_validate_arg(char *line)
{
	int		j;

	j = 0;
	if (line[j] == '-' || line[j] == '+')
		++j;
	while (line[j])
	{
		if (!ft_isdigit(line[j]))
			return (0);
		++j;
	}
	return (1);
}

int		ft_exit(t_all *all)
{
	int		argsize;
	int		valid;

	if ((argsize = ft_strstrlen(all->argv)) == 1)
		exit (0);
	if ((valid = ft_exit_validate_arg(all->argv[1])) && argsize > 2)
		ft_exit_error(NULL, 1);
	else if (valid && argsize == 1)
		exit(ft_atoi(all->argv[1]));
	else if (!valid)
	{
		ft_exit_error(all->argv[1], 0);
		exit(255);
	}
	return (errno);
}
