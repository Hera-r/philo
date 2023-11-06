/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:19:20 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/06 23:29:26 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*xroutine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->end_lock);
	while (!philo->data->end)
	{
		pthread_mutex_unlock(&philo->data->end_lock);
		if (take_forks(philo) == 1)
			break;
		if (xeating(philo) == 1)
			break;
		if (sleeping(philo) == 1)
			break;
		if (print_event("is thinking", philo) == 1)
			break;
		pthread_mutex_lock(&philo->data->end_lock);
	}
	pthread_mutex_unlock(&philo->data->end_lock);
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
	pthread_create(&check_who_eat, NULL, everyone_ate, &philo[0]);
	i = -1;
	while (++i < data.nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
	}
	pthread_join(check_who_eat, NULL);
	return (0);
}
