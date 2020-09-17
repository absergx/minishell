/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:52:58 by memilio           #+#    #+#             */
/*   Updated: 2020/09/17 17:39:50 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t lenght;

	lenght = 0;
	while (str[lenght] != '\0')
	{
		lenght++;
	}
	return (lenght);
}
