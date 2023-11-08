/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:19:20 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/08 23:34:40 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*xroutine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->end_lock);
	while (!philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->end_lock);
		if (take_forks(philo) == 1)
			break ;
		if (xeating(philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
		if (print_event("is thinking", philo) == 1)
			break ;
		if (philo->data->nb_philo % 2)
			ft_usleep(philo->data->eat_time);
		pthread_mutex_lock(&philo->data->end_lock);
	}
	pthread_mutex_unlock(&philo->data->end_lock);
	return (0);
}

void	*thread_1(void *arg)
{
	t_data		*data;
	long int	current;

	data = (t_data *)arg;
	ft_usleep(data->death_time);
	current = current_time() - data->start_time;
	printf("%ld %d die\n", current, 1);
	return (0);
}

int	one_philo(t_data *data)
{
	pthread_t	thread1;

	data->start_time = current_time();
	pthread_create(&thread1, NULL, thread_1, data);
	pthread_join(thread1, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;

	if (parse_init_data(&data, argc, argv) == 1)
		return (0);
	if (data.nb_philo == 1)
		return (one_philo(&data), destroy_mu_data(&data), 0);
	philo = init_xphilo(&data);
	xstart_pthread(&data, philo);
	return (0);
}
