/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:05 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/05 01:21:47 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialize_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		(philo + i)->philo_id = i + 1;
		(philo + i)->meals_eaten = 0;
		(philo + i)->last_meal = get_time();
		(philo + i)->data = data;
		if (pthread_mutex_init((philo + i)->data->fork_mutex + i, NULL) == -1)
			return (str_fd("fork_mutex failed\n", 2), 1);
	}
	mutex_initialiser(philo);
	data->timestamp = get_time();
	if (thread_create(philo))
		return (1);
	return (0);
}

t_data	*data_init(t_data *data, char **av)
{
	data = malloc (sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_count = ft_atoi_prime(av[1]);
	data->time_to_die = ft_atoi_prime(av[2]);
	data->time_to_eat = ft_atoi_prime(av[3]);
	data->time_to_sleep = ft_atoi_prime(av[4]);
	data->number_of_meals = ft_atoi_prime(av[5]);
	data->dead_philo = 0;
	data->fork_mutex = malloc (sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->fork_mutex)
		return (free(data), NULL);
	return (data);
}

pthread_t	*assignment(pthread_t *philo, t_data *data)
{
	philo = malloc (sizeof(*philo) * data->philo_count);
	if (!philo)
		return (free(data), NULL);
	return (philo);
}

int	philo_init(char **av)
{
	t_data			*data;
	t_philo			*philo;

	data = 0;
	data = data_init(data, av);
	if (!data)
		return (1);
	philo = malloc (sizeof(t_philo) * data->philo_count);
	if (!philo)
		return (free(data), 1);
	if (initialize_philo(philo, data))
		return (cleaner(philo), 1);
	monitor(philo);
	join_threads(philo);
	cleaner(philo);
	return (0);
}
