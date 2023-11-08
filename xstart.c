/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstart.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:50:27 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/08 23:34:13 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_init_data(t_data *data, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: number of arguments\n");
		return (1);
	}
	if (xparsing(data, argc, argv) == 1)
	{
		printf("Error: parsing\n");
		return (1);
	}
	if (init_mutex(data) == 1)
		return (1);
	return (0);
}

void	xstart_pthread(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	data->finished = 0;
	data->end = 0;
	data->start_time = current_time();
	while (++i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, xroutine, &philo[i]);
	}
	everyone_ate(data, &philo[0]);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
	}
	destroy_mu_data(data);
	free_philo(philo);
}
