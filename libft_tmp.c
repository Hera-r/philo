

#include "philo.h"

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