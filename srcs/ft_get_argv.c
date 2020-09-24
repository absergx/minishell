/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:46:16 by casubmar          #+#    #+#             */
/*   Updated: 2020/09/22 17:46:17 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_argv(t_all *all, char *str, int start, int last)
{
	char *temp = ft_substr(str, start, last - start);
	char **argv = ft_split(temp, ' '); // пробел в КОВЫЧКАХ
	ft_add_back(&(all->com), argv);

	// Если есть пайп?
	if (all->_pipe)
	{
		t_commas *last;

		last = ft_last_commas(all->com);

	}
	return (1);
}