/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:01 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/08 17:51:47 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	everyone_ate(t_data *data, t_philo *philo)
{
	int	i;

	while (data->end == 0)
	{
		if (data->meals_nb != 0)
		{
			pthread_mutex_lock(&data->last_meal_lock);
			if (data->finished == data->nb_philo)
			{
				pthread_mutex_lock(&data->end_lock);
				data->end = 1;
				pthread_mutex_unlock(&data->end_lock);
				return ;
			}
			pthread_mutex_unlock(&data->last_meal_lock);
		}
		i = 0;
		while (i < data->nb_philo)
		{
			check_last_meals(&philo[i]);
			i++;
		}
		ft_usleep(3);
	}
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
