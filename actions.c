/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:01 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/06 00:14:04 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*everyone_ate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;	
	while (philo->data->end == 0)
	{
		if (philo->data->meals_nb != 0)
		{
			pthread_mutex_lock(&philo->data->last_meal_lock);
			if (philo->data->finished == philo->data->nb_philo)
			{
				pthread_mutex_lock(&philo->data->end_lock);
				philo->data->end = 1;
				pthread_mutex_unlock(&philo->data->end_lock);
				return (0);
			}
			pthread_mutex_unlock(&philo->data->last_meal_lock);
		}
		pthread_mutex_lock(&philo->last_meal_mu);
		if (current_time() >= philo->last_meal)
		{
			print_event("died", philo);
			pthread_mutex_unlock(&philo->last_meal_mu);
			pthread_mutex_lock(&philo->data->end_lock);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->end_lock);
			return (0);
		}
		pthread_mutex_unlock(&philo->last_meal_mu);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{    
		pthread_mutex_lock(philo->l_fork);
		print_event("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print_event("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_event("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_event("has taken a fork", philo);
	}
	return (0);
}

void lock_status_last_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mu);

	philo->last_meal = current_time() + philo->time_to_die;

	pthread_mutex_unlock(&philo->last_meal_mu);
}


int	xeating(t_philo *philo)
{
	lock_status_last_meals(philo);
	print_event("is eating", philo);
	pthread_mutex_lock(&philo->lock);
	philo->eat_cont++;
	if (philo->eat_cont == philo->data->meals_nb)
	{
		pthread_mutex_lock(&philo->data->last_meal_lock);
		philo->data->finished++;
		pthread_mutex_unlock(&philo->data->last_meal_lock);
	}
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->time_eating);
	return (0);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_event("is sleeping", philo);
	ft_usleep(philo->data->sleep_time);
	return (0);
}
