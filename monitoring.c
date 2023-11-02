/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:21:40 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/02 19:36:38 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*xmonitoring(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->data->end)
	{
		if (philo->status == 1 && current_time() >= philo->last_meal)
		{
			pthread_mutex_lock(&philo->data->end_lock);
			print_event("died", philo);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->end_lock);
			break;
		}
	}
	return (0);
}
