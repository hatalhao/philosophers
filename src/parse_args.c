/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:32:32 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/22 01:40:10 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_num(char *s)
{
	if (s && *s == '+')
		s++;
	while (*s)
	{
		if (*s && (*s < '0' || *s > '9'))
			return (write(2, "Invalid Value Provided\n", 23), 0);
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
	long				r;

	i = 0;
	r = 0;
	if (!nptr)
		return (0);
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + nptr[i++] - '0';
		if (off_bound(r))
			return (0);
	}
	return ((int)r);
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
