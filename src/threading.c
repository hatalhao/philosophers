/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:32:24 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/21 21:22:32 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exception_instance(t_philo *philo)
{
	pthread_mutex_lock(philo->data->fork_mutex);
	print(philo, "fork");
	pthread_mutex_unlock(philo->data->fork_mutex);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->philo_count)
		if (pthread_join(philo[i].philo_thread, NULL))
			str_fd("Join failed\n", 2);
}

void	*philo_sequence(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
		exception_instance(philo);
	else
	{
		if (philo->philo_id % 2)
			usleep(philo->data->time_to_eat - 10);
		while (1)
		{
			if (check_death(philo))
				return (NULL);
			took_fork(philo);
			print(philo, "think");
		}
	}
	return (NULL);
}

void	thread_create(t_philo *philo)
{
	int		i;

	i = -1;
	while (++i < philo->data->philo_count)
	{
		if (pthread_create(&philo[i].philo_thread, \
		NULL, &philo_sequence, &philo[i]) != 0)
			return (free (philo->data), free (philo));
	}
}
