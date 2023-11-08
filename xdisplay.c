/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdisplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:08 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/08 23:34:20 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("ERR_TIME\n"), 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	start;

	start = current_time();
	while ((current_time() - start) < time)
		usleep(time * 100);
	return (0);
}

int	print_event(char *str, t_philo *philo)
{
	long int	xtime;

	pthread_mutex_lock(&philo->data->write);
	xtime = current_time() - philo->data->start_time;
	if (xstrcmp(str, "die") == 0 && philo->data->end == 0)
	{
		printf("%ld %d %s\n", xtime, philo->id + 1, str);
		pthread_mutex_lock(&philo->data->end_lock);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->end_lock);
	}
	pthread_mutex_lock(&philo->data->end_lock);
	if (philo->data->end == 0)
		printf("%ld %d %s\n", xtime, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->end_lock);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

void	check_last_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mu);
	if (current_time() >= philo->last_meal)
	{
		print_event("died", philo);
		pthread_mutex_unlock(&philo->last_meal_mu);
		pthread_mutex_lock(&philo->data->end_lock);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->end_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->last_meal_mu);
}

void	lock_status_last_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mu);
	philo->last_meal = current_time() + philo->time_to_die;
	pthread_mutex_unlock(&philo->last_meal_mu);
}
