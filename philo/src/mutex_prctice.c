#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void    *action(void *data)
{
    pthread_t i;

    i = (pthread_t)data;
    printf("person%ld eat\n", i);
    usleep(1000000);
    printf("person%ld sleep\n", i);
}

int main()
{
    pthread_t   person[] = {1, 2, 5, 8};
    long i;

    i = 2;
    pthread_create(person, NULL, action, person[i]);
    /*pthread_create(&person[1], NULL, action, "1");
    pthread_create(&person[2], NULL, action, "2");
    pthread_create(&person[3], NULL, action, "3");
    pthread_create(&person[4], NULL, action, "4");*/
    pthread_join(*person, NULL);
}
