/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdisplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:08 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/02 19:36:31 by hrandria         ###   ########.fr       */
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
	return(0);
}

int	print_event(char *str, t_philo *philo)
{
	long int	xtime;

	if (everyone_ate(philo) == 1)
		return (1);
	else
	{
		pthread_mutex_lock(&philo->data->write);
		xtime = current_time() - philo->data->start_time;
		if (xstrcmp(str, "die") == 0 && philo->data->end == 0)
		{
			printf("%ld %d %s\n", xtime, philo->id + 1, str);
			pthread_mutex_lock(&philo->data->end_lock);
			philo->data->end = 1;
			pthread_mutex_unlock(&philo->data->end_lock);
		}
		else if (philo->data->end == 0)
			printf("%ld %d %s\n", xtime, philo->id + 1, str);
		pthread_mutex_unlock(&philo->data->write);
	}
	return (0);
}
