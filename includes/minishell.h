/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 17:33:12 by memilio           #+#    #+#             */
/*   Updated: 2020/10/12 18:02:30 by memilio          ###   ########.fr       */
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
# include <sys/stat.h>

# define RED "\033[38;5;160m"
# define ENDCOLOR "\033[0m"
# define GREEN "\033[38;5;46m"

typedef struct	s_execute
{
	char		**path;
	char		*temp;
	char		*temp2;
	int			fd;
	char		*res;
	int			status;
	int			is_relative;
}				t_execute;

typedef struct	s_all
{
	int			word_count;
	t_execute	execute;
	int			fds[2];
	char		**argv;
	char		**envp;
	int			size_argv;
	int			have_redir;
}				t_all;

int				g_status;

/*
** main.c
*/

void			ft_promt(void);

/*
** buildins
*/

int				ft_cd(t_all *all);
int				ft_echo(t_all *all);
int				ft_env(t_all *all);
int				ft_exit(t_all *all);
int				ft_export(t_all *all);
int				ft_pwd(t_all *all);
int				ft_unset(t_all *all);

/*
** ft_parse_utils.c
*/

int				skip_spaces(char *str);
int				ft_realloc_argv(t_all *all);
int				ft_new_argv(t_all *all);
int				strstrfree(char **str);
int				ft_add_word_in_argv(t_all *all, char **word);

/*
** ft_parse_fd.c
*/

int				ft_parse_file_name(t_all *all, char *line, int *i, char *redir);
int				ft_create_file(t_all *all, char **word, char *line,
				char *redir);
int				ft_err_fd(t_all *all, char **word, char *line);
int				ft_get_fd(char *redir, char **word);

/*
** ft_parse_redir.c
*/

int				error_redir(char *line, char c, t_all *all);
int				ft_redir(t_all *all, char *line, char *redir);
int				ft_redir_left_or_right(t_all *all, char *line, char **word,
				char *redir);

/*
** ft_parse_quotes.c
*/

int				ft_single_quote(char *line, char **word);
int				ft_double_quote(char *line, char **word, t_all *all);
int				ft_quotes(t_all *all, char *line, char **word);

/*
** ft_parse_env.c
*/

char			*ft_env_res(char *line, int *i, t_all *all, char **word);
char			*ft_get_env(char *line, int *i, t_all *all);
char			*ft_get_env_not_valid_name(char **word, int *i);
char			*ft_get_env_status(char **word, int *i, int len);

/*
** ft_parse_pipe.c
*/

int				ft_find_pipe_or_exec(t_all *all, char **word, char *line);
int				ft_execute_or_pipe(t_all *all, int (*func)(t_all *all),
				char **word, char *line);
int				ft_pipe(t_all *all);

/*
** ft_parse.c
*/

int				ft_parse(char *line, t_all *all);
void			ft_end_parse(t_all *all, char **word);
int				check_valid_start(char *str);
int				ft_check_symbol(t_all *all, char *line, char **word);
char			*ft_add_symbol(char *word, char c);

/*
** ft_error.c
*/

int				ft_error(char **argv, int errcode);
void			check_exit_status(int status);
int				ft_print_error(char *str);
void			ft_malloc_error(void);
void			ft_fork_error(void);

/*
** ft_execute.c
*/

int				ft_execute(t_all *all);

/*
** ft_handle_signal.c
*/

void			ft_eof(void);
void			ft_sigint(int sig);
void			ft_quit(int sig);

/*
** ft_utils.c
*/

int				ft_not_absolute_path(t_all *all);
void			ft_get_path_in_argv(t_all *all);
int				ft_get_envp_key(t_all *all, char *name);
char			*ft_get_envp_value(t_all *all, char *name);

#endif
