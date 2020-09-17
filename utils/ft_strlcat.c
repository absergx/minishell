/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:08:11 by memilio           #+#    #+#             */
/*   Updated: 2020/09/17 17:39:55 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		++i;
	while (src[j] != '\0' && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		++j;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
