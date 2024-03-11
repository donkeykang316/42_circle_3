#include "pipex.h"

int main(int ac, char **av)
{
    int     pid;
    int     i;

    (void)ac;
    i = 0;
    while (av[i])
    { 
        if (av[i + 1])
        {
            printf("error\n");
            av[i] = NULL;
            //free(av[i]);
            av[i] = ft_strdup(av[i + 1]);
        }
        else
            free(av[i + 1]);
        i++;
    }
    printf("error_av:%s  %s\n", av[0], av[1]);
    pid = fork();
    if (!pid)
        execve(av[0], av, NULL);
    else
        printf("parent process\n");
}