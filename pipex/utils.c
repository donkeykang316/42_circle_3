/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:20:20 by kaan              #+#    #+#             */
/*   Updated: 2024/03/16 01:21:08 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **env, char *env_var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], env_var, ft_strlen(env[i])))
			return (ft_strnstr(env[i], env_var, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	**all_path;
	char	**excu;
	int		i;

	i = 0;
	all_path = ft_split(get_env(env, "PATH"), 58);
	excu = ft_split(cmd, 32);
	while (all_path[i])
	{
		path = ft_strdup(all_path[i]);
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, excu[0]);
		free(all_path[i]);
		if (access(path, R_OK | X_OK) != -1)
		{
			free(all_path);
			free(excu);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}
