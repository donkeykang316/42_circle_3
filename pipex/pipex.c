#include "pipex.h"

void	arg_init(t_arg *arg)
{
	arg->content = NULL;
	arg->next = NULL;
}

t_arg	*ft_lstnew_pip(char *content)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_pip(t_arg **lst, t_arg *new)
{
	t_arg	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
	{
		last->next = new;
	}
}

t_arg	*arg_list(t_arg *arg)
{
	t_arg	*new;
}

int	main(int ac, char **av)
{
	t_arg	*arg;
	int	pid;
	int	i;

	(void)ac;
	arg_init(arg);
	i = 1;
	while (av[i])
	{
		arg = ft_lstnew_pip(av[i]);
		ft_lstadd_back_pip(&arg, arg);
		i++;
	}
	printf("error_av:%s  %s\n", av[0], av[1]);
	pid = fork();
	if (!pid)
		execve(av[0], av, NULL);
	else
		printf("parent process\n");
}
