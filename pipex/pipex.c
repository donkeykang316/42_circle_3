/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:18:05 by kaan              #+#    #+#             */
/*   Updated: 2024/03/16 01:44:41 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **temp, char *path, char **exe)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			free(temp[i]);
			i++;
		}
	}
	free(temp);
	if (exe)
	{
		i = 0;
		while (exe[i])
		{
			free(exe[i]);
			i++;
		}
		free(exe);
	}
	if (path)
		free(path);
}

void	cmd_execute(char *cmd, char **env)
{
	char	**temp;
	char	*path;
	char	**exe;
	int		i;
	int		j;

	i = 1;
	j = 0;
	temp = ft_split(cmd, 32);
	path = get_path(cmd, env);
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
	if (execve(path, exe, env) == -1)
		perror("Could not execve\n");
	ft_free(temp, path, exe);
}

void	child_proc(char **av, int *pip_fd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY | O_CREAT, 0777);
	if (fd == -1)
		perror("");
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
		perror("");
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
			perror("");
		pid = fork();
		if (!pid)
			child_proc(av, fd, env);
		else
		{
			main_proc(av, fd, env);
		}
	}
	else
		perror("Not valid argument\n");
}
