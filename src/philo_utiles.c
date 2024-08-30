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
	t_philo	*philo = (t_philo *)arg;
	int flag = 1;

	while (!philo->data->start_exec)
		;
	while (!philo->data->dead_philo)
	{
		if (philo->philo_id % 2 == flag)
			took_fork(philo);
		// if (philo->philo_id % philo->)
		else
			is_thinking(philo);
		// sleep(2);
		if (flag == 1)
			flag = 0;
		else
			flag = 1;
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
	pthread_t		*philo_thread;
	t_philo			*philo;
	t_table			*table;

	i = -1;
	data = 0;
	table = 0;
	philo_thread = 0;
	data = data_init(data, av);
	if (!data)
		return (1);
	table = table_init(table, data);
	if (!table)
		return (free(data), 1);
	philo_thread = assignment(philo_thread, data);
	if (!philo_thread)
		return (free(data), free(table), 1);
	philo = malloc (sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (free(data), free(table), free(philo_thread), 1);
	if (pthread_mutex_init(&data->timestamp_mutex, NULL) == -1)
		return (str_fd("timestamp_mutex failed\n", 2), 1);
	if (pthread_mutex_init(&data->exec_mutex, NULL) == -1)
		return (str_fd("exec_mutex failed\n", 2), 1);
	initialize_philo(philo, data, table, philo_thread);
	if (pthread_mutex_lock(&data->exec_mutex) == 0)
	{
		data->timestamp = get_time();
		data->start_exec = 1;
	}
	if (pthread_mutex_unlock(&data->exec_mutex) == 0)
		;
	i = -1;
	// sleep(2);
	// data->dead_philo = 1;
	while (++i < data->number_of_philosophers)
		if (pthread_join(philo_thread[i], NULL) != 0)
			str_fd("Join failed\n", 2);

	pthread_mutex_destroy(philo->table->fork_mutex);
	free (philo_thread);
	free (data);
	free (philo);
	return (0);
}
