/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:20:13 by memilio           #+#    #+#             */
/*   Updated: 2020/10/06 14:58:57 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_exit_status(int status)
{
 if (WIFEXITED(status))
  g_status = WEXITSTATUS(status);
 else if (WIFSIGNALED(status))
  g_status = WTERMSIG(status) + 128;
}

int		ft_error(char **argv, int errcode)
{
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	if (argv[1])
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errcode), 2);
	ft_putstr_fd(ENDCOLOR, 2);
	return (1);
}
