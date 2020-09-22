/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:17:12 by casubmar          #+#    #+#             */
/*   Updated: 2020/09/21 20:10:58 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_execute(t_all *all)
{
	all->str->str = ft_strtrim(all->str->str, " ");
	if (!(ft_get_argv(all, all->str->str)))
		return ;
	free(all->str->str);
	free(all->str);
	all->str = ft_init_str();
}

void      		 ft_minishell(char *s, t_all *all)
{
	int     i;
	char	c;
	int		quote;

	all->str = ft_init_str();
	c = 0;
	quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ';' && !quote)
		{
			++i;
			ft_execute(all);
		}
		if ((s[i] == '\'' || s[i] == '\"') && !quote)
		{
			c = s[i];
			quote = 1;
		} else if ((s[i] == '\'' || s[i] == '\"') && quote && c == s[i])
		{
			c = 0;
			quote = 0;
		}
		str_add_symbol(all->str, s[i]);
		++i;
	}
	ft_execute(all);
}