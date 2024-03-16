/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:18:05 by kaan              #+#    #+#             */
/*   Updated: 2024/03/16 18:03:49 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_execute(char *cmd, char **env)
{
	char	**temp;
	char	**exe;
	int		i;
	int		j;

	i = 1;
	j = 0;
	temp = ft_split(cmd, 32);
	while (temp[i])
		i++;
	exe = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (temp[i])
	{
		exe[j] = ft_strdup(temp[i]);
		i++;
		j++;
	}
	ft_free(temp);
	if (execve(get_path(cmd, env), exe, env) == -1)
	{
		ft_free(exe);
		ft_exit("");
	}
	ft_free(exe);
}

void	child_proc(char **av, int *pip_fd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		ft_exit("");
	dup2(fd, STDIN_FILENO);
	dup2(pip_fd[1], STDOUT_FILENO);
	close(pip_fd[0]);
	cmd_execute(av[2], env);
}

void	main_proc(char **av, int *pip_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_exit("");
	dup2(fd, STDOUT_FILENO);
	dup2(pip_fd[0], 0);
	close(pip_fd[1]);
	cmd_execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pid;
	int		fd[2];

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			ft_exit("pipe error");
		pid = fork();
		if (pid == -1)
			ft_exit("fork error");
		if (!pid)
			child_proc(av, fd, env);
		else
			main_proc(av, fd, env);
	}
	else
		ft_exit("Not valid argument");
}
