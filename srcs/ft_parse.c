/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:07:27 by casubmar          #+#    #+#             */
/*   Updated: 2020/10/06 15:22:06 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_argv(char **argv)
{
	int i = 0;
	while (argv[i])
	{
		printf("%d - %s\n", i, argv[i]);
		++i;
	}
}

int 	ft_realloc_argv(t_all *all)
{
	char	**new_argv;
	int		i;

	new_argv = ft_calloc(all->size_argv * 2, sizeof(char *));
	i = 0;
	all->size_argv *= 2;
	while (all->argv[i])
	{
		new_argv[i] = ft_strdup(all->argv[i]);
		free(all->argv[i]);
		++i;
	}
	free(all->argv);
	all->argv = new_argv;
	return (1);
}

char 	*ft_add_symbol(char *word, char c)
{
	char	*new_word;
	size_t	i;

	i = 0;
	new_word = 0;
	if (!word)
	{
		word = ft_calloc(1, 2);
		word[0] = c;
		return (word);
	}
	else
	{
		new_word = ft_calloc(ft_strlen(word) + 2, 1);
		while (i < ft_strlen(word))
		{
			new_word[i] = word[i];
			++i;
		}
		new_word[i] = c;
		return (new_word);
	}
}

int 	ft_single_quote(char *line, char **word)
{
	int i = 1;
	if (line[i] == '\'')
	{
		*word = ft_add_symbol(*word, 0);
		return (2);
	}
	while (line[i] != '\'' && line[i])
	{
		*word = ft_add_symbol(*word, line[i]);
		++i;
	}
	++i;
	return (i);
}

char	*ft_get_env(char *line, int *i, t_all *all)
{
	char *word;
	char *res;
	int len;
	int tmp;
	char c;

	tmp = 1;
	len = 0;
	res = 0;
	while (line[tmp] != ' ' && line[tmp] != '"' && line[tmp] \
			&& !ft_strchr("|<>;\\=$'", line[tmp]))
	{
		++tmp;
		++len;
	}
	word = ft_substr(line, 1, len);
	if (!ft_strcmp("?", word))
	{
		res = ft_itoa(g_status);
		*i += len + 1;
		return (res);
	}
	if (!ft_isalnum(word[0]))
	{
		c = word[0];
		free(word);
		word = ft_calloc(3, 1);
		word[0] = '$';
		word[1] = c;
		*i += 2;
		return (word);
	}
	res = ft_get_envp_value(all, word);
	free(word);
	*i += len + 1;
	return (res);
}

char	*ft_env_res(char *line, int *i, t_all *all, char **word)
{
	char *temp;
	int j;

	j = 0;
	//($"'\=)/
	temp = ft_get_env(line + *i, i, all);
	if (!temp)
		*word = ft_add_symbol(*word, 0);
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

int 	ft_double_quote(char *line, char **word, t_all *all)
{
	int i;

	i = 1;
	if (line[i] == '"')
	{
		*word = ft_add_symbol(*word, 0);
		return (2);
	}
	// ($"\)/
	while (line[i] != '"' && line[i])
	{
		if (line[i] == '\\' && ft_strchr("$\"\\", line[i + 1]))
			++i;
		else if (line[i] == '$')
		{
			ft_env_res(line, &i, all, word);
			if (line[i] == '"')
				break;
		}
		*word = ft_add_symbol(*word, line[i]);
		++i;
	}
	++i;
	return (i);
}

int		ft_pipe(t_all *all)
{
	int pid;

	pipe(all->fds);
	pid = fork();
	if (pid == 0)
	{
		if (!all->have_redir)
			dup2(all->fds[1], 1);
		ft_execute(all);
		close(all->fds[0]);
		close(all->fds[1]);
		exit(1);
	}
	else
	{
		wait(0);
		if (all->have_redir)
		{
			dup2(4, 1);
			all->have_redir = 0;
		}
		dup2(all->fds[0], 0);
		close(all->fds[1]);
		close(all->fds[0]);
	}
	return (1);
}

int		ft_create_file(t_all *all, char **word, int *file_name, char *redir)
{
	int fd;

	fd = 0;
	// Закрывать предыдущие открытые файлы
	if (!ft_strcmp("right", redir))
		fd = open(*word, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (!ft_strcmp("left", redir))
		fd = open(*word, O_RDONLY);
	else
		fd = open(*word, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
		fd = -1; // Добавить ошибку
	if (!ft_strcmp("left", redir))
	{
		all->fds[0] = fd;
		// Добавить проверку создания файла
		dup2(all->fds[0], 0);
	}
	else
	{
		all->fds[1] = fd;
		// Добавить проверку создания файла
		dup2(all->fds[1], 1);
	}
	*file_name = 0;
	free(*word);
	*word = 0;
	return (1);
}

int 	ft_add_word_in_argv(t_all *all, char **word)
{
	all->argv[all->parse.word_count] = ft_strdup(*word);
	free(*word);
	*word = 0;// KEK PEK
	all->parse.word_count += 1;
	if (all->parse.word_count == all->size_argv - 1)
		ft_realloc_argv(all);
	return (1);
}

int 	ft_new_argv(t_all *all)
{
	int i;

	i = 0;
	while (all->argv[i])
	{
		free(all->argv[i]);
		++i;
	}
	free(all->argv);
	all->argv = ft_calloc(2, sizeof(char *));
	all->size_argv = 2;
	all->parse.word_count = 0;
	return (1);
}

int 	ft_execute_or_pipe(t_all *all, int (*func)(t_all *all), char **word, char *line)
{
	int i;

	i = 0;
	if (*word)
		ft_add_word_in_argv(all, word);
	func(all);
	ft_new_argv(all);
	++i;
	while (line[i] && line[i] == ' ')
		++i;
	return (i);
}

int 	ft_quotes(t_all *all, char *line, char **word)
{
	int i;

	i = 0;
	if (line[i] == '\'')
	{
		i += ft_single_quote(line + i, word);
	}
	else
	{
		i += ft_double_quote(line + i, word, all);
	}
	return (i);
}

int 	ft_find_pipe_or_exec(t_all *all, char **word, char *line)
{
	int i;

	i = 0;
	if (line[i] == ';')
	{
		i += ft_execute_or_pipe(all, &ft_execute, word, line + i);
		dup2(3, 0);
		dup2(4, 1);
	}
	else if (line[i] == '|')
	{
		i += ft_execute_or_pipe(all, &ft_pipe, word, line + i);
	}
	return (i);
}

int 	ft_redir(t_all *all, char *line, char *redir)
{
	int i;
	char *word;
	int file_name = 1;

	word = NULL;
	i = 1;
	if (line[i] == '>')
	{
		i = 2;
		redir = "double_redir";
	}
	while (line[i] && line[i] == ' ')
		++i;
	if (line[i] == '>' || line[i] == '<')
		return (i); // Добавить ошибку
	while (1)
	{
		if (ft_strchr("| ;><", line[i]) || line[i] == 0)
		{
			ft_create_file(all, &word, &file_name, redir);
			if (line[i] == ' ')
				++i;
			break;
		}
		else
		{
			word = ft_add_symbol(word, line[i]);
			++i;
		}
	}
	return (i);
}

int 	ft_check_symbol(t_all *all, char *line, char **word)
{
	int i;

	i = 0;
	if (line[i] == ' ')
	{
		ft_add_word_in_argv(all, word);
		while (line[i] && line[i] == ' ')
			++i;
	}
	else if (line[i] == '\\')
	{
		*word = ft_add_symbol(*word, line[i + 1]);
		i += 2;
	}
	else if (line[i] == ';' || line[i] == '|')
	{
		i += ft_find_pipe_or_exec(all, word, line + i);
	}
	else if (line[i] == '>')
	{
		all->have_redir = 1;
		if (*word)
			ft_add_word_in_argv(all, word);
		i += ft_redir(all, line + i, "right");
	}
	else if (line[i] == '<')
	{
		all->have_redir = 1;
		if (*word)
			ft_add_word_in_argv(all, word);
		i += ft_redir(all, line + i, "left");
	}
	return (i);
}

int		ft_parse(char *line, t_all *all)
{
	char	*word;
	int		i;

	word = NULL;
	all->have_redir = 0;
	i = 0;
	while (1)
	{
		if (line[i] == 0)
		{
			if (word)
				ft_add_word_in_argv(all, &word);
			ft_execute(all);
			break;
		}
		if (line[i] == '\'' || line[i] == '"')
		{
			i += ft_quotes(all, line + i, &word);
		}
		else if (ft_strchr(" \\<>;|", line[i]))
		{
			i += ft_check_symbol(all, line + i, &word);
		}
		else if (line[i] == '$')
		{
			ft_env_res(line, &i, all, &word);
		}
		else
		{
			word = ft_add_symbol(word, line[i]);
			++i;
		}
	}
	return (1);
}