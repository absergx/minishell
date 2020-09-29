/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:26:48 by memilio           #+#    #+#             */
/*   Updated: 2020/09/29 12:14:39 by memilio          ###   ########.fr       */
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

void	ft_cd_new_argv(t_all *all, char **new_argv)
{
	int		i;

	i = -1;
	while (++i < all->parse.words_count)
		free(all->argv[i]);
	free(all->argv);
	all->argv = new_argv;
	i = -1;
	while (all->argv[i])
		++i;
	all->parse.word_count = i;
}

int		ft_cd(t_all *all)
{
	char	*new_pwd;
	char	**new_argv;

	if (all->parse.word_count == 1)
		chdir(ft_get_envp_value(all, "HOME"));
	else
		chdir(all->argv[1]);
	if (!errno)
	{
		getcwd(new_pwd, NULL);
		new_argv = (char **)malloc(sizeof(char *) * 4);
		new_argv[0] = ft_strdup("export");
		new_argv[1] = ft_strdup("PWD");
		new_argv[2] = new_pwd;
		new_argv[3] = NULL;
		ft_cd_new_argv(all, new_argv);
		ft_export(all);
	}
	return (errno);
}
