/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:48:53 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/02 20:10:11 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_argv(t_data *data, int argc, char *argv[])
{
	if (argc == 6)
		data->meals_nb = xatoi(argv[5]);
	else
		data->meals_nb = 0;
	data->nb_philo = xatoi(argv[1]);
	data->death_time = (long int) xatoi(argv[2]);
	data->eat_time = (long int) xatoi(argv[3]);
	data->sleep_time = (long int) xatoi(argv[4]);
	if (data->nb_philo < 0)
		return (1);
	if (data->death_time < 0 || data->eat_time < 0 || \
		data->sleep_time < 0 || data->meals_nb < 0)
		return (1);
	return (0);
}

t_philo	*init_xphilo(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		tmp;

	philo = malloc((data->nb_philo) * sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo) * data->nb_philo);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].id = i;
		philo[i].l_fork = &data->forks[philo[i].id];
		tmp = (philo[i].id + 1) % data->nb_philo;
		philo[i].r_fork = &data->forks[tmp];
		philo[i].time_eating = data->eat_time;
		philo[i].time_to_die = data->death_time;
		pthread_mutex_init(&philo[i].lock, NULL);
		pthread_mutex_init(&philo[i].status_lock, NULL);
		philo[i].data = data;
		i++;
	}
	return (philo);
}

int	pre_init(t_data *data)
{
	if (pthread_mutex_init(&data->must_die, NULL) != 0)
		return (perror("pthread_mutex_init"), 1);
	if (pthread_mutex_init(&data->end_lock, NULL) != 0)
		return (perror("pthread_mutex_init"), 1);
	if (pthread_mutex_init(&data->must_eat, NULL) != 0)
		return (perror("pthread_mutex_init"), 1);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (perror("pthread_mutex_init"), 1);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (perror("pthread_mutex_init"), 1);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pre_init(data);
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if(!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (perror("pthread_mutex_init"), 1);
		i++;
	}
	return (0);
}
