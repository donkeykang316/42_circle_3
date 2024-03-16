/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaan <kaan@student.42.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:18:18 by kaan              #+#    #+#             */
/*   Updated: 2024/03/16 18:14:56 by kaan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libraries/libft/inc/libft.h"

typedef struct s_tmp
{
	char	*temp;
	char	*temp1;
	char	*path;
	char	**all_path;
	char	**excu;
	int		i;
}		t_tmp;

char	*get_env(char **env, char *env_var);
char	*get_path(char *cmd, char **env);
void	ft_exit(char *error);
void	ft_free(char **ptr);

#endif
