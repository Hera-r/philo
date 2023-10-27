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
	int				eating;
	int				time_to_die;
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
	int				death_time;
	long int		eat_time;
	int				sleep_time;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_data;

long int	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (printf("ERR_TIME\n"), 1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(long int time)
{
	long int	start;
	start = current_time();
	while ((current_time() - start) < time)
		usleep(time / 10);
	return(0);
}

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (1);
	return (0);
}

int	isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	xatoi(const char *nptr)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	sign = 1;
	n = 0;
	while (is_space(nptr[i]))
	i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (isdigit(nptr[i]))
	{
		n = n * 10 + (nptr[i] - '0');
	i++;
	}
	return (n * sign);
}

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

void	destroy_mutex(pthread_mutex_t *data, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&data[i]);
		i++;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if(!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (destroy_mutex(data->forks, data->nb_philo), 1);
		i++;
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	long int	xtime;

	if (pthread_mutex_lock(&philo->l_fork) != 0)
		return (printf("Error pthread_mutex_lock\n", 1));
	xtime = current_time() - philo->data->start_time;
	printf("%ld %d has taken a fork\n", xtime, philo->id);
	if (pthread_mutex_lock(&philo->r_fork) != 0)
		return (printf("Error pthread_mutex_lock\n", 1));
	xtime = current_time() - philo->data->start_time;
	printf("%ld %d has taken a fork\n", xtime, philo->id);
	return (0);
}

void	xeating(t_philo *philo)
{
	long int	xtime;

	xtime = current_time() - philo->data->start_time;
	printf("%ld %d is eating\n", xtime, philo->id);
	ft_usleep(philo->eating);
}

int	sleeping(t_philo *philo)
{
	long int	xtime;

	if (pthread_mutex_unlock(&philo->l_fork) != 0)
		return (printf("Error pthread_mutex_unlock\n", 1));
	if (pthread_mutex_unlock(&philo->r_fork) != 0)
		return (printf("Error pthread_mutex_unlock\n", 1));
	xtime = current_time() - philo->data->start_time;
	printf("%ld %d is sleeping\n", xtime, philo->id);
	ft_usleep(philo->eating);
	return (0);
}

void	thinking(t_philo *philo)
{
	long int	xtime;

	xtime = current_time() - philo->data->start_time;
	printf("%ld %d is thinking\n", xtime, philo->id);
	ft_usleep(philo->eating);
}


t_philo	*init_xphilo(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		tmp;

	philo = malloc((data->nb_philo) + sizeof(t_philo));
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
		philo[i].eating = &data->eat_time;
		philo[i].data = data;
	}
	return (philo);
}

int	init_argv(t_data *data, int argc, char *argv[])
{
	if (argc == 6)
		data->meals_nb = xatoi(argv[5]);
	else
		data->meals_nb = 0;
	data->nb_philo = xatoi(argv[1]);
	data->death_time = xatoi(argv[2]);
	data->eat_time = xatoi(argv[3]);
	data->sleep_time = xatoi(argv[4]);
	if (data->nb_philo <= 1 || data->death_time < 0 || 
		data->eat_time < 0 || data->sleep_time || data->meals_nb < 0)
		return (1);
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
		return (0);
	return (1);
}

void	*xroutine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		take_forks(philo);
		xeating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	pthread_t	*philo;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("error 1\n");
		return (0);
	}
	if (xparsing(&data, argc, argv) == 1)
		return (0);

	// if (init_mutex(&data) == 1)
	// 	return (0);
	// i = 0;
	// philo = init_xphilo(&data);
	data.start_time = current_time();

	return (0);
}




// https://github.com/TommyJD93/Philosophers#step1











// pthread_mutex_t *forks;

// void *philosopher(void *num) {
//     int philosopher_number = *((int *)num);
//     int left_fork = philosopher_number;
//     int right_fork = (philosopher_number + 1) % *((int *)num); // Utilisation du nombre de philosophes

//     // Boucle infinie pour que les philosophes puissent manger indéfiniment
//     while (1) {
//         // Attendre que les fourchettes soient disponibles
//         pthread_mutex_lock(&forks[left_fork]);
//         pthread_mutex_lock(&forks[right_fork]);

//         // Manger
//         printf("Philosophe %d mange\n", philosopher_number);

//         // Libérer les fourchettes
//         pthread_mutex_unlock(&forks[left_fork]);
//         pthread_mutex_unlock(&forks[right_fork]);
//     }
// }


//     forks = (pthread_mutex_t *)malloc(num_philosophers * sizeof(pthread_mutex_t));

//     pthread_t *philosophers = (pthread_t *)malloc(num_philosophers * sizeof(pthread_t));
//     int *phil_numbers = (int *)malloc(num_philosophers * sizeof(int));

//     // Initialiser les mutex pour les fourchettes
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_mutex_init(&forks[i], NULL);
//     }

//     // Créer les threads des philosophes
//     for (int i = 0; i < num_philosophers; i++) {
//         phil_numbers[i] = i;
//         pthread_create(&philosophers[i], NULL, philosopher, (void *)&num_philosophers); // Passer le nombre de philosophes
//     }

//     // Attendre la fin des threads (ce qui ne se produira jamais car les philosophes mangent indéfiniment)
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_join(philosophers[i], NULL);
//     }

//     // Détruire les mutex pour les fourchettes
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_mutex_destroy(&forks[i]);
//     }

//     free(forks);
//     free(philosophers);
//     free(phil_numbers);

