/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:19:20 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/05 23:57:34 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy_philo_resources(t_data *data)
{
	free(data->thread);
	free(data->forks);
	pthread_mutex_destroy(&data->secure);
	pthread_mutex_destroy(&data->last_meal_lock);
	pthread_mutex_destroy(&data->must_die);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->must_eat);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	data = NULL;
}

void	*xroutine(void *arg)
{
	t_philo		*philo;
	// pthread_t	check_who_die;

	philo = (t_philo *)arg;
	// pthread_create(&check_who_die, NULL, xmonitoring, philo);
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo->time_eating);
	while (!philo->data->end)
	{
		// ft_usleep(philo->time_eating *0.7);
		if (take_forks(philo) == 1)
			break;
		if (xeating(philo) == 1)
			break;
		if (sleeping(philo) == 1)
			break;
		if (print_event("is thinking", philo) == 1)
			break;
	}
	return (0);
}

int	one_philo(t_data *data)
{
	long int current;

	data->start_time = current_time();
	ft_usleep(data->death_time);
	current = current_time() - data->start_time;
	printf("%ld %d die\n", current, 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;
	int			i;
	pthread_t	check_who_eat;

	if (argc < 5 || argc > 6)
	{
		printf("error 1\n");
		return (0);
	}
	if (xparsing(&data, argc, argv) == 1)
	{
		printf("Error argv\n");
		return (0);
	}
	if (data.nb_philo == 1)
		return (one_philo(&data));
	if (init_mutex(&data) == 1)
		return (0);
	philo = init_xphilo(&data);
	i = -1;
	data.finished = 0;
	data.end = 0;
	data.start_time = current_time();
	while (++i < data.nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, xroutine, &philo[i]);
	}
	if (philo->data->meals_nb != 0)
		pthread_create(&check_who_eat, NULL, everyone_ate, &philo[0]);
	i = -1;
	while (++i < data.nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
	}
	if (philo->data->meals_nb != 0)
		pthread_join(check_who_eat, NULL);
	// destroy_philo_resources(&data);
	return (0);
}
