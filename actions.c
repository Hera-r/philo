

#include "philo.h"

int	everyone_ate(t_philo *philo)
{
	int	total;

	total = philo->data->nb_philo * philo->data->meals_nb;
	if (philo->data->meals_nb != 0)
	{
		if (philo->eat_cont == philo->data->meals_nb)
		{
			if (pthread_mutex_lock(&philo->data->must_eat) != 0)
				return (printf("pthread_mutex_lock"), 1);
			philo->data->finished += philo->data->meals_nb;
			fprintf(stderr, "FINISHED %d\n", philo->data->finished);
			if (pthread_mutex_unlock(&philo->data->must_eat) != 0)
				return (printf("pthread_mutex_lock\n"), 1);
			if (philo->data->finished == total)
			{
				philo->data->end = 0;
				fprintf(stderr,"ENTRE ICI\n");
				return (1);
			}
		}
	}
	return (0);
}


int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (printf("pthread_mutex_lock"), 1);
	if (print_event("has taken a fork", philo) == 1)
		return (1);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (printf("pthread_mutex_lock"), 1);
	if (print_event("has taken a fork", philo) == 1)
		return (1);
	return (0);
}

int	xeating(t_philo *philo)
{
	if (print_event("is eating", philo) == 1)
		return (1);
	if (philo->data->meals_nb != 0)
	{
		if (pthread_mutex_lock(&philo->data->must_eat) != 0)
			return (printf("pthread_mutex_lock"), 1);
		philo->eat_cont++;
		if (pthread_mutex_unlock(&philo->data->must_eat) != 0)
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
	if (print_event("is sleeping", philo) == 1)
		return (1);
	ft_usleep(philo->data->sleep_time);
	return (0);
}
