#include "../includes/philo.h"

t_table	*table_init(t_table	*table, t_data *data)
{
	table = malloc (sizeof(t_table));
	if (!table)
		return (free(data), NULL);
	table->fork_id = malloc (sizeof(int) * data->number_of_forks);
	table->fork_mutex = malloc (sizeof(pthread_mutex_t) * data->number_of_forks);
	return (table);
}
void	*philo_sequence(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead_philo)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		took_fork(philo);
		is_thinking(philo);
	}
	return (NULL);
}

pthread_t	*assignment(pthread_t *philo, t_data *data)
{
	philo = malloc (sizeof(*philo) * data->number_of_philosophers);
	if (!philo)
		return (free(data), NULL);
	return (philo);
}

t_data	*data_init(t_data *data, char **av)
{
	data = malloc (sizeof(t_data));
	if (!data)
		return (NULL);
	data->timestamp = 0;
	data->dead_philo = 0;
	data->number_of_philosophers = ft_atoi_prime(av[1]);
	data->time_to_die = ft_atoi_prime(av[2]);
	data->time_to_eat = ft_atoi_prime(av[3]);
	data->time_to_sleep = ft_atoi_prime(av[4]);
	if (av[5])
		data->number_of_meals = ft_atoi_prime(av[5]);
	else
		data->number_of_meals = 0;
	data->number_of_forks = data->number_of_philosophers;
	return (data);
}

int	philo_init(char **av)
{
	int				i;
	t_data			*data;
	t_philo			*philo;
	t_table			*table;

	i = -1;
	data = 0;
	table = 0;
	data = data_init(data, av);
	if (!data)
		return (1);
	table = table_init(table, data);
	if (!table)
		return (free(data), 1);
	philo = malloc (sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (free(data), free(table), 1);
	data->timestamp = get_time();
	printf("*************** HERE ******************\n");
	initialize_philo(philo, data, table);
	monitor(philo);
	while (++i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].philo_thread, NULL))
			str_fd("Join failed\n", 2);
	}
	destroy_mutex(philo);
	// pthread_mutex_lock(&data->death_mutex);
	// if (data->dead_philo)
	// 	pthread_mutex_unlock(&data->death_mutex);
	// else
	// 	pthread_mutex_unlock(&data->death_mutex);
	free (table->fork_id);
	free (table->fork_mutex);
	free (table);
	free (data);
	free (philo);
	return (0);
}
