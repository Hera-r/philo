/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:21:07 by hrandria          #+#    #+#             */
/*   Updated: 2023/11/06 23:34:24 by hrandria         ###   ########.fr       */
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
	long int		last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t last_meal_mu;
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
	int				end;
	long int		death_time;
	long int		eat_time;
	long int		sleep_time;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	must_eat;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	must_die;
	pthread_mutex_t	secure;
	pthread_mutex_t last_meal_lock;

}					t_data;

void		*xroutine(void *arg);
void		*xmonitoring(void *arg);
int			xeating(t_philo *philo);
int			print_event(char *str, t_philo *philo);
int			xatoi(const char *nptr);
int			isdigit(int c);
int			all_digit(char *argv[]);
int			xparsing(t_data *data, int argc, char *argv[]);
int			init_argv(t_data *data, int argc, char *argv[]);
int			take_forks(t_philo *philo);
int			init_mutex(t_data *data);
int			sleeping(t_philo *philo);
int			ft_usleep(long int time);
int			xstrcmp(char *s1, char *s2);
long int	current_time(void);

void		*everyone_ate(void *philo);

t_philo		*init_xphilo(t_data *data);


#endif