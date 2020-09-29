/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 11:45:03 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
#include <stdio.h>

//#include "minishell.h"

int		ft_pwd(t_all *all)
{
	char	*path;

	if ((path = getcwd(NULL, 0)))
	{
		ft_putstr_fd(path, 1);
		free(path);
	}
	(void)all;
	return (errno);
}
