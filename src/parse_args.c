#include "../includes/philo.h"

void	is_num(char *s)
{
	while (s && *s)
	{
		if (*s && (*s < '0' || *s > '9'))
		{
			write(2, "Invalid Value Provided\n", 23);
			exit (1);
		}
		s++;
	}
}

void	off_bound(long nb)
{
	if (nb > INT_MAX || nb < INT_MIN)
	{
		write(2, "Not an Integer\n", 15);
		exit (1);
	}
}

int	ft_atoi_prime(char const *nptr)
{
	int					i;
	int					s;
	long				r;

	i = 0;
	s = 1;
	r = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + nptr[i++] - '0';
		off_bound((r * s));
	}
	return ((int)(r * s));
}

void	check_args(char **av)
{
	while (*av)
	{
		is_num(*av);
		ft_atoi_prime(*av);
		av++;
	}
}
