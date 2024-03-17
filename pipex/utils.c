/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:20:20 by kaan              #+#    #+#             */
/*   Updated: 2024/03/17 15:00:07 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char *error)
{
	perror(error);
	exit(0);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
}

char	*get_env(char **env, char *env_var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env_var, env[i], 4))
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	t_tmp	tmp;

	tmp.i = 0;
	tmp.all_path = ft_split(get_env(env, "PATH"), 58);
	tmp.excu = ft_split(cmd, 32);
	while (tmp.all_path[tmp.i])
	{
		tmp.temp = ft_strdup(tmp.all_path[tmp.i]);
		tmp.temp1 = ft_strjoin(tmp.temp, "/");
		free(tmp.temp);
		tmp.path = ft_strjoin(tmp.temp1, tmp.excu[0]);
		free(tmp.temp1);
		if (access(tmp.path, R_OK | X_OK) != -1)
		{
			ft_free(tmp.all_path);
			ft_free(tmp.excu);
			return (tmp.path);
		}
		free(tmp.path);
		tmp.i++;
	}
	ft_free(tmp.all_path);
	ft_free(tmp.excu);
	return (NULL);
}
