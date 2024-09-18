#include "../includes/philo.h"

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	usleep(time * 1000 * 0.9);
	while ((get_time() - start) < time)
		usleep(10);
}

void	thread_create(t_philo *philo)
{
	int		i;

	i = -1;
	while(++i < philo->data->number_of_philosophers) 
	{
		if (pthread_create(&philo[i].philo_thread, NULL, &philo_sequence, &philo[i]) != 0)
		{
			free (philo->data);
			free (philo);
		}
	}
}

long	get_time(void)
{
	struct timeval	tv;
	if (gettimeofday(&tv, NULL))
		printf("Problem in get_time\n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	monitor(t_philo *philo)
{
	int				k;
	unsigned long	t;
	int				meals;

	meals = philo->data->number_of_meals;
	while (1)
	{
		k = -1;
		pthread_mutex_lock(&philo->data->meals_mutex);
		while (meals && (++k < philo->data->number_of_philosophers)\
		&& ((philo + k)->meals_eaten == meals))
		{
			if (k == philo->data->number_of_philosophers)
			{
				pthread_mutex_unlock(&philo->data->meals_mutex);
				return ;
			}
		}
		pthread_mutex_unlock(&philo->data->meals_mutex);
		k = -1;
		while (++k < philo->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->data->last_meal_mutex);
			t = (unsigned long)(philo + k)->last_meal;
			pthread_mutex_unlock(&philo->data->last_meal_mutex);
			if ((unsigned long)(philo + k)->data->time_to_die <= (get_time() - t))
			{
				philo_died(philo + k);
				pthread_mutex_lock(&(philo + k)->data->death_mutex);
				if (philo->data->dead_philo)
				{
					pthread_mutex_unlock(&(philo + k)->data->death_mutex);
					return ;
				}
				pthread_mutex_unlock(&(philo + k)->data->death_mutex);
			}
		}
	}
}

void	initialize_philo(t_philo *philo, t_data *data, t_table *table)
{
	int	i;

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
		(philo + i)->last_meal = get_time();
		table->fork_id[i] = i;
		(philo + i)->data = data;
		(philo + i)->table = table;
		mutex_initialiser(philo);
		if (pthread_mutex_init((philo + i)->table->fork_mutex + i, NULL) == -1)
			return (str_fd("fork_mutex failed\n", 2), exit(3), (void)NULL);
	}
	thread_create(philo);
}
