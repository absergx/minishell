/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:12:28 by memilio           #+#    #+#             */
/*   Updated: 2020/10/01 14:39:29 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint(int sig)
{
	int		pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_status = 130;
		if (pid)
			ft_promt();
	}
}

void	ft_eof(void)
{
	ft_putendl_fd("\n exit", 1);
	exit(0);
}

void	ft_quit(int sig)
{
	int		pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, WNOHANG);
	if (!pid)
		ft_putendl_fd("Quit: 3", 1);
	else
		ft_putstr_fd("\b\b \b\b", 1);
}
