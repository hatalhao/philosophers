/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:35:58 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/22 00:40:18 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	usleep(time * 100);
	while ((get_time() - start) < time)
		usleep(10);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		printf("Problem in get_time\n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
