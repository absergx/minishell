/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:20:13 by memilio           #+#    #+#             */
/*   Updated: 2020/10/13 15:09:33 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_error(void)
{
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putendl_fd(ENDCOLOR, 2);
	exit(1);
}

void	check_exit_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}

int		ft_print_error(char *str)
{
	g_status = 1;
	ft_putstr_fd(RED"minishell: ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd(ENDCOLOR, 2);
	return (1);
}

int		ft_error(char **argv, int errcode, char *str)
{
	if (!g_status)
		g_status = 1;
	ft_putstr_fd(RED"minishell: ", 2);
	if (!str)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	else if (argv[1])
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
	}
	if (errcode)
		ft_putendl_fd(strerror(errcode), 2);
	else
		ft_putendl_fd("command not found", 2);
	ft_putstr_fd(ENDCOLOR, 2);
	return (1);
}
