

#include "philo.h"

// int	everyone_ate(t_philo *philo)
// {
// 	if (philo->eat_cont == philo->data->meals_nb)
// 	{
// 		if (pthread_mutex_lock(&philo->data->finished) != 0)
// 			return (printf("pthread_mutex_lock"), 1);
// 		philo->data->finished += philo->data->meals_nb;
// 	}
// 	if (pthread_mutex_lock(&philo->data->finished) != 0)
// 		return (printf("pthread_mutex_lock\n"), 1);
// 	if (philo->data->finished == (philo->data->meals_nb * philo->data->meals_nb))
// 		return (1);
// 	return (0);
// }


int	take_forks(t_philo *philo)
{
	long int	xtime;

	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (printf("pthread_mutex_lock"), 1);
	
	xtime = current_time() - philo->data->start_time;
	printf("%ld %d has taken a fork\n", xtime, philo->id + 1);

	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (printf("pthread_mutex_lock"), 1);

	xtime = current_time() - philo->data->start_time;
	printf("%ld %d has taken a fork\n", xtime, philo->id + 1);
	return (0);
}

int	xeating(t_philo *philo)
{
	
	print_event("is eating", philo);
	if (philo->data->meals_nb != 0)
	{
		if (pthread_mutex_lock(&philo->data->write) != 0)
			return (printf("pthread_mutex_lock\n"), 1);
		philo->eat_cont++;
		if (pthread_mutex_unlock(&philo->data->write) != 0)
			return (printf("Error pthread_mutex_unlock\n"), 1);
	}
	ft_usleep(philo->time_eating);
	return (0);
}


int	sleeping(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (printf("Error pthread_mutex_unlock\n"), 1);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (printf("Error pthread_mutex_unlock\n"), 1);
	print_event("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
	return (0);
}


// int	check_philoshopher_dead(t_philo *philo)
// {
// 	long int	current;
// 	long int	elapsed;

// 	current = current_time();
// 	elapsed = current - l
// }