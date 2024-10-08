/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:35:58 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/05 04:53:01 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(unsigned long time, t_philo *philo)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (philo && check_death(philo))
			return ;
		usleep(10);
	}
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		str_fd("Problem in get_time\n", 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
