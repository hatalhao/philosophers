#include "../includes/philo.h"

void	get_time(t_philo *philo)
{
	struct timeval	tv;
	if (gettimeofday(&tv, NULL))
		printf("Problem in get_time\n");
		// printf("tv == %ld\n", tv.tv_usec);
	// usleep();
	if (pthread_mutex_lock(&philo->data->timestamp_mutex) == 0)
		philo->data->timestamp = tv.tv_usec * 1000;
	if (pthread_mutex_unlock(&philo->data->timestamp_mutex) == 0)
		;
}

void	*monitor(void	*arg)
{
	int		k;
	t_philo	*philo;

	philo = arg;
	while (!philo->data->start_exec)
		;
	while (1)
	{
		k = -1;
		while (++k < philo->data->number_of_philosophers)
		{
			if ((philo + (k % philo->data->number_of_philosophers))->data->dead_philo)
				pthread_exit(&philo->data->exit_status);
			// printf("k == %d\n", k);
			usleep(100);
		}
		k = 0;
		while (philo->data->number_of_meals && k < philo->data->number_of_philosophers\
		&& (philo + k)->meals_eaten == philo->data->number_of_meals)
		{
			if (k == philo->data->number_of_philosophers)
				break ;
			philo[k] = *(philo + k)->next;
			k++;
		}
	}
	return (NULL);
}

void	initialize_philo(t_philo *philo, t_data *data, t_table *table, pthread_t *philo_thread)
{
	pthread_t	monitor_thread;
	int			i;

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
		(philo + i)->data = data;
		(philo + i)->table = table;
		if (pthread_mutex_init((philo + i)->table->fork_mutex + i, NULL) == -1)
			return (str_fd("fork_mutex failed\n", 2), exit(3), (void)NULL);
		
		if (pthread_create(philo_thread + i, NULL, &philo_sequence, philo + i) != 0)
		{
			free (philo_thread);
			free (data);
			free (philo);
		}
		if (pthread_create(&monitor_thread, NULL, &monitor, philo) != 0)
		{
			// free (monitor_thread);
			free (philo_thread);
			free (data);
			free (philo);
		}
	}
}
