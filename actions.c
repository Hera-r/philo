/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:01 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/02 19:37:28 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyone_ate(t_philo *philo)
{
	if (philo->data->meals_nb != 0)
	{
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->must_eat);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->must_eat);
			if (philo->data->finished == philo->data->nb_philo)
			{
				pthread_mutex_unlock(&philo->data->end_lock);
				philo->data->end = 1;
				pthread_mutex_unlock(&philo->data->end_lock);
				return (1);
			}
		}
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_event("has taken a fork", philo) == 1)
		return (1);
	pthread_mutex_lock(philo->r_fork);
	if (print_event("has taken a fork", philo) == 1)
		return (1);
	return (0);
}

void	lock_status_last_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->status_lock);
	philo->last_meal = current_time() + philo->time_to_die;
	philo->status = 0;
	pthread_mutex_unlock(&philo->status_lock);
}

int	xeating(t_philo *philo)
{
	lock_status_last_meals(philo);
	if (print_event("is eating", philo) == 1)
		return (1);
	if (philo->data->meals_nb != 0)
	{
		pthread_mutex_lock(&philo->lock);
		philo->eat_cont++;
		pthread_mutex_unlock(&philo->lock);
	}
	ft_usleep(philo->time_eating);
	pthread_mutex_lock(&philo->status_lock);
	philo->status = 1;
	pthread_mutex_unlock(&philo->status_lock);
	return (0);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (print_event("is sleeping", philo) == 1)
		return (1);
	ft_usleep(philo->data->sleep_time);
	return (0);
}
