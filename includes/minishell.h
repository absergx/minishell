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

typedef struct			s_commas
{
	char 				**argv;
	int 				fds[2];
	struct s_commas 	*next;
}						t_commas;

typedef struct  s_str
{
	int			buff;
	int			last_index;
	char		*str;
}               t_str;

typedef struct  s_all
{
	t_str		*str;
	t_commas	*com;
}               t_all;

t_str       *ft_init_str(void);
int			str_add_symbol(t_str *str, char c);
void        ft_minishell(char *s, t_all *all);
t_commas	*ft_new_commas(char **content);
int 		ft_add_back(t_commas **head, char **content);
void		ft_commas_clear(t_commas *head);
int			ft_get_argv(t_all *all, char *str);

#endif
