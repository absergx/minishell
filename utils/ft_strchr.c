/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 22:08:35 by memilio           #+#    #+#             */
/*   Updated: 2020/09/17 17:40:38 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *string, int symbol)
{
	while (*string != '\0')
	{
		if (symbol == *string)
			return ((char *)string);
		++string;
	}
	if (symbol == *string)
		return ((char *)string);
	return (NULL);
}
