#include "pipex.h"

void	arg_init(t_arg *arg, char **av)
{
	arg->filename1 = ft_strdup(av[1]);
	arg->cmd1 = ft_strdup(av[2]);
	arg->path1 = NULL;
	arg->agm1 = NULL;
	arg->cmd2 = ft_strdup(av[3]);
	arg->path2 = NULL;
	arg->agm2 = NULL;
	arg->filename2 = ft_strdup(av[4]);
}

void	file1_check(t_arg *argv, int *fd)
{
	if (access(argv->filename1, R_OK) != -1)
		*fd = open(argv->filename1, O_RDONLY);
	else
		perror("");
}

void	cmd1_exp(t_arg *argv)
{
	char	**temp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	temp = ft_split(argv->cmd1, ' ');
	argv->path1 = ft_strdup("/usr/bin/");
	argv->path1 = ft_strjoin(argv->path1, temp[0]);
	while (temp[i])
		i++;
	argv->agm1 = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (temp[i])
	{
		argv->agm1[j] = ft_strdup(temp[i]);
		free(temp[i]);
		i++;
		j++;
	}
	argv->agm1[j] = ft_strdup(argv->filename1);
	free(temp);
}

void	cmd2_exp(t_arg *argv)
{
	char	**temp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	temp = ft_split(argv->cmd2, ' ');
	argv->path2 = ft_strdup("/usr/bin/");
	argv->path2 = ft_strjoin(argv->path2, temp[0]);
	while (temp[i])
		i++;
	argv->agm2 = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (temp[i])
	{
		argv->agm2[j] = ft_strdup(temp[i]);
		free(temp[i]);
		i++;
		j++;
	}
	free(temp);
}

int	main(int ac, char **av)
{
	t_arg	*argv;
	int		pid;
	int		fd;

	if (ac == 5)
	{
		argv = malloc(sizeof(t_arg));
		arg_init(argv, av);
		file1_check(argv, &fd);
		cmd1_exp(argv);
		cmd2_exp(argv);
		pid = fork();
		if (!pid)
		{
			if (execve(argv->path1, argv->agm1, NULL) == -1)
				perror("Could not execve\n");
		}
		else
		{
		//	waitpid(pid);
			if (execve(argv->path2, argv->agm2, NULL) == -1)
				perror("Could not execve\n");
		}
		close(fd);
	}
	else
		perror("Not valid argument\n");
}
