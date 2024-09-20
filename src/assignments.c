/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:56:05 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/20 23:27:47 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		(philo + i)->philo_id = i + 1;
		(philo + i)->meals_eaten = 0;
		(philo + i)->last_meal = get_time();
		data->fork_id[i] = i;
		(philo + i)->data = data;
		mutex_initialiser(philo);
		if (pthread_mutex_init((philo + i)->data->fork_mutex + i, NULL) == -1)
			return (str_fd("fork_mutex failed\n", 2));
	}
	thread_create(philo);
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
	if (av[5])
		data->number_of_meals = ft_atoi_prime(av[5]);
	data->fork_id = malloc (sizeof(int) * data->philo_count);
	if (!data->fork_id)
		return (free(data), NULL);
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
	int				i;
	t_data			*data;
	t_philo			*philo;

	i = -1;
	data = 0;
	data = data_init(data, av);
	if (!data)
		return (1);
	printf("----> %d\n", data->number_of_meals);
	sleep (3);
	philo = malloc (sizeof(t_philo) * data->philo_count);
	if (!philo)
		return (free(data), 1);
	data->timestamp = get_time();
	initialize_philo(philo, data);
	monitor(philo);
	join_threads(philo);
	cleaner(philo);
	return (0);
}
