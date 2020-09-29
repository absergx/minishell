/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:33:12 by memilio           #+#    #+#             */
/*   Updated: 2020/09/28 14:02:56 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>

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
}               t_all;

int		ft_parse(char *line, t_all *all);
char	*ft_get_envp_value(t_all *all, char *name);

#endif
