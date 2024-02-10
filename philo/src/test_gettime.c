#include "../inc/philo.h"

int	main(int ac, char **av)
{
	struct timeval	c_time;
    gettimeofday(&c_time, NULL);
	printf("sec:%ld milisec:%ld\n", c_time.tv_sec, c_time.tv_usec);
    sleep (2);
    gettimeofday(&c_time, NULL);
	printf("sec:%ld milisec:%ld\n", c_time.tv_sec, c_time.tv_usec);
}