/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:22:15 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 16:59:08 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(void)
{
	char	*line;

	line = NULL;
	if (get_next_line(3, &line) < 0)
		ft_putstr_fd("Error\n", 2);
	return (line);
}

int		main(int argc, char **argv, char **envp)
{
	int		status;
	// char	*line;
	t_all	all;
	char	**new_argv;
	int		i;

	all.envp = (char **)malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	i = 0;
	while (envp[i])
	{
		all.envp[i] = ft_strdup(envp[i]);
		++i;
	}
	status = 1;
	dup2(0, 3);
	dup2(1, 4);
	new_argv = (char **)malloc(sizeof(char *) * ft_strstrlen(argv));
	i = 0;
	while (i < argc - 1)
	{
		new_argv[i] = argv[i + 1];
		++i;
	}
	new_argv[i] = NULL;
	all.argv = new_argv;
	if (!ft_strcmp(all.argv[0], "exit"))
		ft_exit(&all);
	else if (!ft_strcmp(all.argv[0], "cd"))
	{
		ft_cd(&all);
		ft_pwd(&all);
		printf("-----------------------------------\n");
		ft_env(&all);
	}
	else if (!ft_strcmp(all.argv[0], "echo"))
		ft_echo(&all);
	else if (!ft_strcmp(all.argv[0], "env"))
		ft_env(&all);
	else if (!ft_strcmp(all.argv[0], "export"))
	{
		ft_export(&all);
		printf("-----------------------------------\n");
		printf("-----------------------------------\n");
		printf("-----------------------------------\n");
		ft_env(&all);
	}
	else if (!ft_strcmp(all.argv[0], "pwd"))
		ft_pwd(&all);
	else if (!ft_strcmp(all.argv[0], "unset"))
	{
		ft_unset(&all);
		printf("-----------------------------------\n");
		printf("-----------------------------------\n");
		printf("-----------------------------------\n");
		ft_env(&all);
	}
	else
		ft_putendl_fd("unknown command", 1);
	(void)argc;
	return (0);
}
