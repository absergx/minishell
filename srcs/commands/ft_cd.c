/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:26:48 by memilio           #+#    #+#             */
/*   Updated: 2020/10/08 18:42:55 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_write_argv(t_all *all, char *old_pwd)
{
	char	**new_argv;
	int		i;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!(new_argv = (char **)malloc(sizeof(char *) * 4)))
		ft_malloc_error();
	if (!(new_argv[0] = ft_strdup("export"))
	|| !(new_argv[1] = ft_strjoin("PWD=", new_pwd))
	|| !(new_argv[2] = ft_strjoin("OLDPWD=", old_pwd)))
		ft_malloc_error();
	new_argv[3] = NULL;
	i = -1;
	while (all->argv[++i])
		free(all->argv[i]);
	free(all->argv);
	all->argv = new_argv;
	ft_export(all);
	if (new_pwd)
		free(new_pwd);
	return (errno);
}

int			ft_cd(t_all *all)
{
	
	char	*old_pwd;
	char	*home;

	old_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (ft_strstrlen(all->argv) == 1)
	{
		if ((home = ft_get_envp_value(all, "HOME")))
			chdir(home);
		else
		{
			ft_print_error("cd: HOME not set");
			return (errno);
		}
	}
	else
		chdir(all->argv[1]);
	if (!errno)
		ft_cd_write_argv(all, old_pwd);
	if (old_pwd)
		free(old_pwd);
	return (errno);
}
