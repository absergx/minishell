/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:33:12 by memilio           #+#    #+#             */
/*   Updated: 2020/09/21 19:02:28 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>

typedef struct  s_str
{
	int			buff;
	int			last_index;
	char		*str;
}               t_str;

typedef struct  s_all
{
	t_str		*str;
	int			_pipe;
}               t_all;

t_str       *ft_init_str(void);
int			str_add_symbol(t_str *str, char c);
void        ft_minishell(char *s, t_all *all);

#endif
