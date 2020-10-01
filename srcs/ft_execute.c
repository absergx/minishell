#include "minishell.h"

int		ft_execute_our(t_all *all)
{
	if (!ft_strcmp(all->argv[0], "exit"))
		return (ft_exit(all));
	else if (!ft_strcmp(all->argv[0], "cd"))
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

int 	ft_execute(t_all *all)
{
	char	**path;
	char	*temp;
	char	*temp2;
	int 	i;
	int 	fd;
	char 	*res;
	int		pid;

	if ((i = ft_execute_our(all)) != -1)
		return (i);
	i = 0;
	fd = 0;
	temp = ft_get_envp_value(all, "PATH");
	free(temp);
	path = ft_split(temp, ':');
	errno = 0;
	g_status = 0;
	res = NULL;
	while (path[i])
	{
		temp2 = ft_strjoin(path[i], "/");
		temp = ft_strjoin(temp2, all->argv[0]);
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
	pid = fork();
	if (pid == 0)
	{
		exit (execve(res, all->argv, all->envp));
	}
	else
		wait(0);
	return (1);
}