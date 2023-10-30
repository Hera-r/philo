

#include "philo.h"

int	print_event(char *str, t_philo *philo)
{
	long int	xtime;

	if (pthread_mutex_lock(&philo->data->lock) != 0)
		return (printf("pthread_mutex_lock"), 1);
	xtime = current_time() - philo->data->start_time;
	printf("%ld %d %s\n", xtime, philo->id + 1, str);
	if (pthread_mutex_unlock(&philo->data->lock) != 0)
		return (printf("Error pthread_mutex_unlock\n"), 1);
	return (0);
}