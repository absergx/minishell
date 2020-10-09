#include "minishell.h"

int		ft_execute_our(t_all *all)
{
	if (!ft_strcmp(all->argv[0], "cd"))
		return (ft_cd(all));
	else if (!ft_strcmp(all->argv[0], "echo"))
		return (ft_echo(all));
	else if (!ft_strcmp(all->argv[0], "env"))
		return (ft_env(all));
	else if (!ft_strcmp(all->argv[0], "export"))
		return (ft_export(all));
	else if (!ft_strcmp(all->argv[0], "pwd"))
		return (ft_pwd(all));
	else if (!ft_strcmp(all->argv[0], "unset"))
		return (ft_unset(all));
	return (-1);
}

int		ft_not_absolute_path(t_all *all)
{
	if (all->argv[0] && ft_strchr("./", all->argv[0][0]))
		return (0);
	return (1);
}

int 	ft_execute(t_all *all)
{
	char	**path;
	char	*temp;
	char	*temp2;
	int 	i;
	int 	fd;
	char 	*res;
	int		pid;
	int		status;
	int		is_relative;

	if (all->argv[0] == 0)
		return (1);
	if (!ft_strcmp(all->argv[0], "exit"))
		return (ft_exit(all));
	errno = 0;
	g_status = 0;
	if ((i = ft_execute_our(all)) != -1)
	{
		if (errno)
			ft_error(all->argv, errno);
		return (i);
	}
	i = 0;
	fd = 0;
	temp = ft_get_envp_value(all, "PATH");
	if (!temp)
		temp = ft_strdup("");
	path = ft_split(temp, ':');
	free(temp);
	res = NULL;
	if ((is_relative = ft_not_absolute_path(all)))
		while (path[i])
		{
			if (!(temp2 = ft_strjoin(path[i], "/")))
				ft_malloc_error();
			if (!(temp = ft_strjoin(temp2, all->argv[0])))
				ft_malloc_error();
			if ((fd = open(temp, O_RDONLY)) > 0)
			{
				res = temp;
				break ;
			}
			free(temp);
			free(temp2);
			++i;
		}
	if (!res)
		res = all->argv[0];
	strstrfree(path);
	fd = open(res, O_RDONLY);
	if (fd < 0)
	{
		errno = is_relative ? 0 : 2;
		g_status = 127;
		ft_error(all->argv, errno);
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		exit (execve(res, all->argv, all->envp));
	}
	else
	{
		wait(&status);
		check_exit_status(status);
//		if (temp)
//			free(temp);
//		if (temp2)
//			free(temp2);
	}
	return (1);
}