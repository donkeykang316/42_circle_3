#ifndef PIPEX_H
# define    PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libraries/libft/inc/libft.h"

typedef struct	s_arg
{
	char    		*content;
	struct s_arg	*next;
}	t_arg;


#endif
