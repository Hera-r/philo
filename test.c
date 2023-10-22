#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
	int				id;
	int				nb_philo;
	pthread_t		*philospher;
	pthread_mutex_t	*forks;

}				t_pihlo;

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


int all_digit(char *argv[])
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




void	*philosopher(void *init)
{
	t_data	*data;
	int		id;

	
	data = (t_data*)init;
	left_fork = id;
	right_fork = (id + 1) % data.nb_philo;
	while (1)
	{

	}
	

}


int main(int argc, char *argv[])
{
	t_data	data;
	int nb_philo;

	if (argc < 5 || argc > 6)
		return (0);
	if (all_digit(argv) == 1)
		return (0);
	nb_philo = xatoi(argv[1]);
	if (nb_philo < 2)
		return (0);
	data = init_philo(nb_philo);




	return (0);
}










// https://github.com/TommyJD93/Philosophers#step1



// pthread_mutex_t	*inti_forks(int nb_philo)
// {
// 	pthread_mutex_t	*forks;
// 	int				i;

// 	i = 1;
// 	forks = malloc(nb_philo * sizeof(pthread_mutex_t));
// 	if (!forks)
// 		return ;
// 	while (i <= nb_philo)
// 	{
// 		if (pthread_mutex_init(&forks[i], NULL) != 0)
// 			return (free(forks), NULL);
// 		i++;
// 	}
// 	return (forks);
// }

// t_data	init_philo(int nb_philo)
// {
// 	t_data	data;

// 	data.nb_philo = nb_philo;
// 	data.philospher = tab_pihlo(nb_philo);
// 	data.forks = inti_forks(nb_philo);

// 	return (data);
// }







	// philo = malloc(nb_philo * sizeof(pthread_t));
	// if (!philo)
	// 	return ;



// // Définir la fonction que chaque "lutin" (thread) va exécuter
// void* travailDuLutin(void* numero) {
//     int num = *(int*)numero;
	
//     if (num == 1) {
//         printf("Le lutin 1 dessine un soleil.\n");
//     } else if (num == 2) {
//         printf("Le lutin 2 écrit une lettre.\n");
//     }

//     return NULL;
// }

// int main() {
//     // Préparer les "lutins"
//     pthread_t lutin1, lutin2;
//     int num1 = 1, num2 = 2;

//     // Dire aux "lutins" ce qu'ils vont faire


//     pthread_create(&lutin1, NULL, travailDuLutin, (void*)&num1);


//     pthread_create(&lutin2, NULL, travailDuLutin, (void*)&num2);

//     // Attendre que les "lutins" finissent leur travail
//     pthread_join(lutin1, NULL);
//     pthread_join(lutin2, NULL);

//     return 0;
// }




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

