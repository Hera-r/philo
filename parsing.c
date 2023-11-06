/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:49:24 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/06 23:29:41 by hrandria         ###   ########.fr       */
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
	{
		printf("Is not digit\n");
		return (1);
	}
	if (init_argv(data, argc, argv) == 1)
		return (1);
	return (0);
}