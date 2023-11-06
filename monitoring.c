/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:21:40 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/06 00:26:53 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*xmonitoring(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->data->end == 0)
	{
		// pthread_mutex_lock(&philo->last_meal_mu);
		if (current_time() >= philo->last_meal)
		{
			print_event("died", philo);
			pthread_mutex_lock(&philo->data->end_lock);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->end_lock);
			return (0);
		}
		// pthread_mutex_unlock(&philo->last_meal_mu);
	}
	return (0);
}

// void	destroy_exit(t_data *data)
// {
// 	Nettoyage des ressources (mutex)
// 	i = 0;
// 	while (i < data.nb_philo)
// 	{
// 		pthread_mutex_destroy(&philo[i].l_fork);
// 		pthread_mutex_destroy(&philo[i].r_fork);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&data.end_lock);
// 	pthread_mutex_destroy(&data.must_eat);
// 	pthread_mutex_destroy(&data.lock);
// 	pthread_mutex_destroy(&data.write);
// 	free(data.forks);
// 	free(philo);
// }