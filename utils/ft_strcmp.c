/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 00:22:24 by memilio           #+#    #+#             */
/*   Updated: 2020/09/17 17:44:48 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	size_t i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		++i;
	}
	if (str1[i] != str2[i])
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
