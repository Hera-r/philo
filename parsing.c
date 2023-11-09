/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:24 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/10 00:07:10 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_digit(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j] != '\0')
		{
			if (!isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	xparsing(t_data *data, int argc, char *argv[])
{
	if (all_digit(argv) == 1)
		return (1);
	if (init_argv(data, argc, argv) == 1)
		return (1);
	return (0);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	destroy_mu_data(t_data *data)
{
	pthread_mutex_destroy(&data->last_meal_lock);
	pthread_mutex_destroy(&data->must_die);
	pthread_mutex_destroy(&data->end_lock);
	pthread_mutex_destroy(&data->must_eat);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->write);
	destroy_forks(data);
}

void	free_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].lock);
		pthread_mutex_destroy(&philo[i].last_meal_mu);
		i++;
	}
	free(philo);
}
