#ifndef PIPEX_H
# define    PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libraries/libft/inc/libft.h"

typedef struct s_arg
{
	char	*filename1;
	char	*path1;
	char	*cmd1;
	char	**agm1;
	char	*path2;
	char	*cmd2;
	char	**agm2;
	char	*filename2;
}	t_arg;

#endif
