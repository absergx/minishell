/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 16:59:36 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_all *all)
{
	char	*path;

	if ((path = getcwd(NULL, 0)))
	{
		ft_putendl_fd(path, 1);
		free(path);
	}
	(void)all;
	return (errno);
}
