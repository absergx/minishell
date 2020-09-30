/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:26:48 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 12:19:07 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_new_argv(t_all *all, char **new_argv)
{
	int		i;

	i = -1;
	while (all->argv[++i])
		free(all->argv[i]);
	free(all->argv);
	all->argv = new_argv;
}

static int	ft_cd_write_argv(t_all *all, char *new_pwd, char *old_pwd)
{
	char	**new_argv;

	new_argv = (char **)malloc(sizeof(char *) * 4);
	if (!(new_argv[0] = ft_strdup("export"))
	&& !(new_argv[1] = ft_strjoin("PWD=", new_pwd))
	&& !(new_argv[2] = ft_strjoin("OLDPWD=", old_pwd))
	&& !(new_argv[3] = NULL))
		return (errno);
	ft_cd_new_argv(all, new_argv);
	ft_export(all);
	return (errno);
}

int			ft_cd(t_all *all)
{
	char	*new_pwd;
	char	*old_pwd;
	

	getcwd(old_pwd, NULL);
	if (ft_strstrlen(all->argv) == 1)
		chdir(ft_get_envp_value(all, "HOME"));
	else
		chdir(all->argv[1]);
	if (!errno)
	{
		getcwd(new_pwd, NULL);
		ft_cd_write_argv(all, new_pwd, old_pwd);
		if (new_pwd)
			free(new_pwd);
	}
	if (old_pwd)
		free(old_pwd);
	return (errno);
}
