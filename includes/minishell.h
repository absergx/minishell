/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:33:12 by memilio           #+#    #+#             */
/*   Updated: 2020/09/30 18:50:13 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef struct	s_parse
{
	int			word_s;
	int			word_e;
	int			word_count;
	int			quotes;
	int 		space_before;
}				t_parse;

typedef struct  s_all
{
	t_parse		parse;
	int 		fds[2];
	char		**argv;
	char 		**envp;
	int 		size_argv;
	int 		status;
}               t_all;

int		ft_parse(char *line, t_all *all);
char	*ft_get_envp_value(t_all *all, char *name);
int 	ft_execute(t_all *all);
void	print_argv(char **argv);
int		ft_get_envp_key(t_all *all, char *name);
int		ft_cd(t_all *all);
int		ft_echo(t_all *all);
int		ft_env(t_all *all);
int		ft_exit(t_all *all);
int		ft_export(t_all *all);
int		ft_pwd(t_all *all);
int		ft_unset(t_all *all);

#endif
