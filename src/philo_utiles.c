#include "../includes/philo.h"

t_table	*table_init(t_table	*table, t_data *data)
{
	table = malloc (sizeof(t_table));
	if (!table)
		return (free(data), exit(1), NULL);
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
		if (philo->philo_id % (philo->data->number_of_philosophers / 2) == flag)
			took_fork(philo);
		else
			is_thinking(philo);
		// printf("flag == %d\n", flag);
		sleep(2);
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
	else
		data->number_of_meals = 0;
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
	int				k;

	k = -1;
	i = -1;
	data = 0;
	data = data_init(data, av);
	philo = malloc (sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (free(data), exit(1), (void)NULL);
	table = 0;
	table = table_init(table, data);
	philo_thread = 0;
	philo_thread = assignment(philo_thread, data);
	
	for (int j = 0; j < data->number_of_philosophers; j++)
	{
		(philo + j)->data = data;
		(philo + j)->table = table;
	}

	if (!philo->table->fork_mutex)
		return (free(data), free(philo_thread), free(philo), exit(1), (void)NULL);
	
	while (++i < philo->data->number_of_forks)
	{
		if (pthread_mutex_init(philo->table->fork_mutex, NULL) == -1)
			return (str_fd("fork_mutex failed\n", 2), exit(3), (void)NULL);
	}

	if (pthread_mutex_init(&philo->data->timestamp_mutex, NULL) == -1)
		return (str_fd("timestamp_mutex failed\n", 2), exit(3), (void)NULL);
	
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		(philo + i)->philo_id = i + 1;
		if (i == data->number_of_philosophers - 1)
			(philo + i)->next = philo;
		else
			(philo + i)->next = philo + i + 1; 
		(philo + i)->left_fork = 0;
		(philo + i)->right_fork = 0;
		(philo + i)->meals_eaten = 0;
		(philo + i)->last_meal = 0;
		table->fork_id[i] = i;
		if (pthread_create(philo_thread + i, NULL, &philo_sequence, philo + i) != 0)
		{
			free (philo_thread);
			free (data);
			free (philo);
		}
	}
	philo->data->start_exec = 1;
	
	while (1)
	{	if (data->dead_philo)
			pthread_exit(&data->exit_status);
		while (data->number_of_meals && k < data->number_of_philosophers && (philo + k)->meals_eaten == data->number_of_meals)
		{
			if (k == data->number_of_philosophers)
				break ;
			philo[k] = *(philo + k)->next;
			k++;
		}
		k = 0;
	}
	for (i = 0; i < data->number_of_philosophers; i++)
	{
		if (pthread_join(philo_thread[i], NULL) != 0)
			str_fd("Join failed\n", 2);
	}
	
	pthread_mutex_destroy(philo->table->fork_mutex);
	free (philo_thread);
	free (data);
	free (philo);
}
