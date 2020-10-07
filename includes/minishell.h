/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:33:12 by memilio           #+#    #+#             */
/*   Updated: 2020/10/07 17:23:28 by casubmar         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

# define RED "\033[38;5;160m"
# define ENDCOLOR "\033[0m"
# define GREEN "\033[38;5;46m"

typedef struct	s_parse
{
	int			word_s;
	int			word_e;
	int			word_count;
	int 		space_before;
}				t_parse;

typedef struct  s_all
{
	t_parse		parse;
	int 		fds[2];
	char		**argv;
	char 		**envp;
	int 		size_argv;
	int			have_redir;
}               t_all;

int				g_status;

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
int 	ft_realloc_argv(t_all *all);
char 	*ft_add_symbol(char *word, char c);
int 	ft_single_quote(char *line, char **word);
char	*ft_get_env(char *line, int *i, t_all *all);
char	*ft_env_res(char *line, int *i, t_all *all, char **word);
int 	ft_double_quote(char *line, char **word, t_all *all);
int		ft_pipe(t_all *all);
int		ft_create_file(t_all *all, char **word, int *file_name, char *redir);
int 	ft_add_word_in_argv(t_all *all, char **word);
int 	ft_new_argv(t_all *all);
int 	ft_execute_or_pipe(t_all *all, int (*func)(t_all *all), char **word, char *line);
int 	ft_quotes(t_all *all, char *line, char **word);
int 	ft_find_pipe_or_exec(t_all *all, char **word, char *line);
int 	ft_redir(t_all *all, char *line, char *redir);
int 	ft_check_symbol(t_all *all, char *line, char **word);
void	ft_eof(void);
void	ft_sigint(int sig);
void	ft_quit(int sig);
void	ft_promt(void);
int		ft_error(char **argv, int errcode);
void	check_exit_status(int status);
int		ft_print_error(char *str);
int		skip_spaces(char *str);

#endif
