/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:21:07 by hrandria          #+#    #+#             */
/*   Updated: 2023/10/19 00:11:38 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SUCCESS 1
# define FAIL 0
# define INT_MIN -2147483648
# define INT_MAX +2147483647

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				eat_cont;
	int				status;
	long int		time_eating;
	long int		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	t_philo			*thread;
	int				nb_philo;
	int				meals_nb;
	int				dead;
	int				finished;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

void		*xroutine(void *arg);
int			xeating(t_philo *philo);
int			print_event(char *str, t_philo *philo);
int			xatoi(const char *nptr);
int			isdigit(int c);
int			all_digit(char *argv[]);
int			xparsing(t_data *data, int argc, char *argv[]);
int			init_argv(t_data *data, int argc, char *argv[]);
int			everyone_ate(t_philo *philo);
int			take_forks(t_philo *philo);
int			init_mutex(t_data *data);
int			sleeping(t_philo *philo);
int			ft_usleep(long int time);
long int	current_time(void);

t_philo		*init_xphilo(t_data *data);


#endif