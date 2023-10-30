/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:19:20 by hrandria          #+#    #+#             */
/*   Updated: 2023/10/20 16:26:07 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*xroutine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		take_forks(philo);
		xeating(philo);
		sleeping(philo);
		print_event("is thinking", philo);
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		*philo;
	int			i;

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
	if (init_mutex(&data) == 1)
		return (0);
	philo = init_xphilo(&data);
	data.start_time = current_time();
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, xroutine, &philo[i]);
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}

	return (0);
}