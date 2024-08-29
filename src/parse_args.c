#include "../includes/philo.h"

int	is_num(char *s)
{
	while (s && *s)
	{
		if (*s && (*s < '0' || *s > '9'))
		{
			write(2, "Invalid Value Provided\n", 23);
			return (0);
		}
		s++;
	}
	return (1);
}

int	off_bound(long nb)
{
	return ((nb > INT_MAX || nb < INT_MIN));
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
		if (off_bound((r * s)))
			return (0);
	}
	return ((int)(r * s));
}

int	check_args(char **av)
{
	while (*av)
	{
		if (!is_num(*av) || !ft_atoi_prime(*av))
			return (1);
		av++;
	}
	return (0);
}
