/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:35:02 by memilio           #+#    #+#             */
/*   Updated: 2020/09/24 18:44:55 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

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

int		ft_pwd(char **argv, char **envp)
{
	char	*path;
	int		errno;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	return (errno);
}

int main(void)
{
	ft_pwd();
	return (0);
}
