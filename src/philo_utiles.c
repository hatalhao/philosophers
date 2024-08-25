#include "../includes/philo.h"

void	ops_(pthread_mutex_t *mutex, int *k)
{
	mutex_lock_unlock(mutex, k);
}

void	mutex_lock_unlock(pthread_mutex_t *mutex, int *k)
{
	(void)mutex;
	pthread_mutex_lock(mutex);
	// printf("MUTEX WORKS\n");
	printf("-------> %d\n", *k);
	(*k)++;
	usleep(300000);
	pthread_mutex_unlock(mutex);

}

void	*philo_sequence(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	while (!philo->data->start_exec)
		;
	philo->;
	return (NULL);
}

pthread_t	*assignment(pthread_t *philo, t_data *data)
{
	philo = malloc (sizeof(*philo) * data->number_of_philosophers);
	if (!philo)
		return (free(data), exit(1), NULL);
	return (philo);
}

t_data	*data_init(t_data *data, char **av)
{
	data = malloc (sizeof(t_data));
	if (!data)
		return (exit(1), NULL);
	data->timestamp = 0;
	data->dead_philo = 0;
	data->number_of_philosophers = ft_atoi_prime(av[1]);
	data->time_to_die = ft_atoi_prime(av[2]);
	data->time_to_eat = ft_atoi_prime(av[3]);
	data->time_to_sleep = ft_atoi_prime(av[4]);
	if (av[5])
		data->number_of_meals = ft_atoi_prime(av[5]);
	data->number_of_forks = data->number_of_philosophers;
	return (data);
}

void	philo_init(char **av)
{
	int				i;
	t_data			*data;
	pthread_t		*philo_thread;
	t_philo			*philo;
	t_table			*table;

	i = -1;
	data = 0;
	data = data_init(data, av);
	philo = malloc (sizeof(t_philo));
	if (!philo)
		return (free(data), exit(1), (void)NULL);
	table = malloc (sizeof(t_table));
	if (!table)
		return (free(data), exit(1), (void)NULL);
	philo_thread = 0;
	philo_thread = assignment(philo_thread, data);
	if (!philo_thread)
		return (free(data), exit(1), (void)NULL);
	
	philo->data = data;
	philo->table = table;
	philo->table->fork_mutex = malloc (sizeof(pthread_mutex_t) * data->number_of_forks);
	if (!philo->table->fork_mutex)
		return (free(data), free(philo_thread), free(philo), exit(1), (void)NULL);
	
	if (pthread_mutex_init(philo->table->fork_mutex, NULL) == -1)
		return (str_fd("fork_mutex failed\n", 2), exit(3), (void)NULL);
	if (pthread_mutex_init(&philo->data->timestamp_mutex, NULL) == -1)
		return (str_fd("timestamp_mutex failed\n", 2), exit(3), (void)NULL);
	while (++i < data->number_of_philosophers)
	{
		philo->philo_id = i + 1;
		philo->left_fork = i + 1;
		if (pthread_create(philo_thread + i, NULL, &philo_sequence, philo) != 0)
		{
			free (philo_thread);
			free (data);
			free (philo);
		}
		printf("philo_thread[%d] ==  %lu\n", i, philo_thread[i]);
	}

	philo->data->start_exec = 1;
	// printf("id in sq = %d\n", id);
	for (i = 0; i < data->number_of_philosophers; i++)
		pthread_join(philo_thread[i], NULL);
	free (philo_thread);
	free (data);
	free (philo);
}
