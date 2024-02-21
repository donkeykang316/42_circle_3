#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo {
    long time_to_die;
} t_philo;

typedef struct s_monitor {
    t_philo *philo;
    pthread_t mon;
} t_monitor;

void *monitoring(void *data);

int main() {
    t_philo philo_data;
    t_monitor monitor;

    // Allocate memory for philo
    monitor.philo = (t_philo *)malloc(sizeof(t_philo));
    if (monitor.philo == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Set time_to_die
    monitor.philo->time_to_die = 500;

    // Create thread
    if (pthread_create(&(monitor.mon), NULL, monitoring, (void *)&monitor)) {
        printf("Error creating thread\n");
        free(monitor.philo); // Free previously allocated memory
        return 1;
    }

    // Join thread
    pthread_join(monitor.mon, NULL);

    // Free allocated memory
    free(monitor.philo);

    return 0;
}

void *monitoring(void *data) {
    t_monitor *monitor;
    monitor = (t_monitor *)data;
    printf("Time to die: %ld\n", monitor->philo->time_to_die);
    return NULL;
}