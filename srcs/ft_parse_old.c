/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:16:21 by memilio           #+#    #+#             */
/*   Updated: 2020/09/28 16:19:25 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//
//#include "minishell.h"
//
//char	**ft_add_argv(char **argv, int words)
//{
//	char	**new_argv;
//	int		i;
//
//	i = -1;
//	if (!(new_argv = (char **)malloc(sizeof(char *) * (words + 2))))
//		return (NULL); // call error
//	if (words == 0)
//	{
//		while (++i < 2)
//			new_argv[i] = NULL;
//		return (new_argv);
//	}
//	while (++i < words)
//		new_argv[i] = argv[i];
//	new_argv[i] = NULL;
//	new_argv[i + 1] = NULL;
//	free(argv);
//	return (new_argv);
//}
//
//int		ft_check_quotes(t_all *all)
//{
//	int		i;
//
//	i = 0;
//	while (all->argv[all->parse.word_count - 1][i])
//	{
//		if (all->argv[all->parse.word_count - 1][i] == '\'')
//		{
//			if (!all->parse.quotes)
//				all->parse.quotes = 1;
//			else if (all->parse.quotes == 1)
//				all->parse.quotes = 0;
//			break ;
//		}
//		else if (all->argv[all->parse.word_count - 1][i] == '"')
//		{
//			if (!all->parse.quotes)
//				all->parse.quotes = 2;
//			else if (all->parse.quotes == 2)
//				all->parse.quotes = 0;
//			break ;
//		}
//		++i;
//	}
//	return (1);
//}
//
//char	*ft_rejoin(char *str1, t_all *all, char *line)
//{
//	char	*res;
//	char	*str2;
//
//	if (!(str2 = ft_substr(line, all->parse.word_s,
//			(size_t)(all->parse.word_e - all->parse.word_s + 1))))
//		return (NULL);
//	if (!(res = ft_strjoin(str1, str2)))
//		return (NULL);
//	if (str1)
//		free(str1);
//	if (str2)
//		free(str2);
//	return (res);
//}
//
//int		ft_add_word(t_all *all, char *line)
//{
//	if (!all->parse.quotes)
//	{
//		if (!(all->argv = ft_add_argv(all->argv, all->parse.word_count)))
//			return (0); // Malloc error
//		if (!(all->argv[all->parse.word_count] = ft_substr(line, all->parse.word_s,
//			(size_t)(all->parse.word_e - all->parse.word_s + 1))))
//			return (0); // Malloc error
//		all->parse.word_count += 1;
//	}
//	else
//	{
//		if (!(all->argv[all->parse.word_count - 1] = ft_rejoin(all->argv[all->parse.word_count - 1], all, line)))
//			return (0);
//	}
//	ft_skip_spaces(line, &all->parse.word_e);
//	all->parse.word_s = all->parse.word_e;
//	all->parse.word_e -= 1;
//	return (1);
//}
//
//void	print_argv(char **argv)
//{
//	int i = 0;
//	while (argv[i])
//	{
//		printf("%s\n", argv[i]);
//		++i;
//	}
//}
//
//int 	ft_parse_single_qutes(t_all *all, char *line)
//{
//	char *word;
//
//	if (all->parse.space_before)
//	{
//		all->parse.word_count += 1;
//		if (!(all->argv = ft_add_argv(all->argv, all->parse.word_count)))
//			return (0);
//	}
//	word = all->argv[all->parse.word_count - 1];
//	printf("word - %s\n", word);
//	(void)line;
//	return (1);
//}
//
//int		ft_parse(char *line, t_all *all)
//{
//	if (!line)
//		return (0);
//	while (1)
//	{
//		if (!line[all->parse.word_e])
//		{
//			if (all->parse.word_s != all->parse.word_e && !ft_add_word(all, line))
//				exit(1);
//			break;
//		}
//		else if (line[all->parse.word_e] == ' ' && !ft_add_word(all, line))
//			return (0);
//		else if (line[all->parse.word_e] == '\'')
//		{
//			if (all->parse.word_e - 1 >= 0 && line[all->parse.word_e - 1] == ' ')
//				all->parse.space_before = 1;
//			all->parse.word_e = ft_parse_single_qutes(all, line);
//		}
//		else
//			all->parse.word_e += 1;
//	}
//	print_argv(all->argv);
//	return (1);
//}
