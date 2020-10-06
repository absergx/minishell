/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:26:48 by memilio           #+#    #+#             */
/*   Updated: 2020/10/06 16:19:54 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_write_argv(t_all *all, char *new_pwd, char *old_pwd)
{
	char	**new_argv;
	int		i;

	new_argv = (char **)malloc(sizeof(char *) * 4);
	if (!(new_argv[0] = ft_strdup("export"))
	|| !(new_argv[1] = ft_strjoin("PWD=", new_pwd))
	|| !(new_argv[2] = ft_strjoin("OLDPWD=", old_pwd)))
		return (errno);
	new_argv[3] = NULL;
	i = -1;
	while (all->argv[++i])
		free(all->argv[i]);
	free(all->argv);
	all->argv = new_argv;
	ft_export(all);
	return (errno);
}

int			ft_cd(t_all *all)
{
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = NULL;
	old_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (ft_strstrlen(all->argv) == 1)
		chdir(ft_get_envp_value(all, "HOME"));
	else
		chdir(all->argv[1]);
	if (!errno)
	{
		new_pwd = getcwd(NULL, 0);
		ft_cd_write_argv(all, new_pwd, old_pwd);
		if (new_pwd)
			free(new_pwd);
	}
	if (old_pwd)
		free(old_pwd);
	return (errno);
}
