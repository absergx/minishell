/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:23:58 by casubmar          #+#    #+#             */
/*   Updated: 2020/09/21 16:41:02 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str       *ft_init_str(void)
{
	t_str *new;

	if (!(new = (t_str *)malloc(sizeof(t_str))))
		return 0;
	new->buff = 100;
	new->last_index = 0;
	if(!(new->str = ft_calloc(new->buff + 1, 1)))
		return (0);
	return (new);
}

int			str_add_symbol(t_str *str, char c)
{
	char *new;

	if (str->last_index + 2 >= str->buff)
	{
		if (!(new = ft_calloc(str->buff * 2 + 1, 1)))
			return (0);
		ft_memmove(new, str->str, str->buff);
		free(str->str);
		str->str = new;
		str->buff *= 2;
	}
	str->str[str->last_index] = c;
	++(str->last_index);
	return (1);
}