/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:02:25 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 17:04:27 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_status(char **word, int *i, int len)
{
	char	*res;

	if (!(res = ft_itoa(g_status)))
		ft_malloc_error();
	*i += len + 1;
	free(*word);
	return (res);
}

char	*ft_get_env_not_valid_name(char **word, int *i)
{
	char	c;
	char	*res;

	c = (*word)[0];
	free(*word);
	if (!(res = ft_calloc(3, 1)))
		ft_malloc_error();
	res[0] = '$';
	res[1] = c;
	*i = res[1] ? *i + 2 : *i + 1;
	return (res);
}

char	*ft_get_env(char *line, int *i, t_all *all)
{
	char	*word;
	char	*res;
	int		len;

	len = 0;
	res = 0;
	while (line[len + 1] != ' ' && line[len + 1] != '"' && line[len + 1] \
			&& !ft_strchr("|<>;\\=$'", line[len + 1]))
		++len;
	if (!(word = ft_substr(line, 1, len)))
		ft_malloc_error();
	if (!ft_strcmp("?", word))
		return (ft_get_env_status(&word, i, len));
	if (!ft_isalnum(word[0]) && word[0] != '_')
		return (ft_get_env_not_valid_name(&word, i));
	res = ft_get_envp_value(all, word);
	free(word);
	*i += len + 1;
	return (res);
}

char	*ft_env_res(char *line, int *i, t_all *all, char **word)
{
	char	*temp;
	int		j;

	j = 0;
	temp = ft_get_env(line + *i, i, all);
	if (!temp)
		*word = NULL;
	else
	{
		while (temp[j])
		{
			*word = ft_add_symbol(*word, temp[j]);
			++j;
		}
		free(temp);
		temp = NULL;
	}
	return (NULL);
}
