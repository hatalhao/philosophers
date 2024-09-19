#include "../includes/philo.h"

int	monitor_death(t_philo *philo)
{
	unsigned long	last_meal;
	int				k;
	
	k = -1;
	while (++k < philo->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		last_meal = (unsigned long)(philo + k)->last_meal;
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		if ((unsigned long)(philo + k)->data->time_to_die <= (get_time() - last_meal))
			return (print(philo + k, "die"), 1);
	}
	return (0);
}

int	check_meals(t_philo *philo, int meals)
{
	int k = -1;
	pthread_mutex_lock(&philo->data->meals_mutex);
	while (meals && (++k < philo->data->number_of_philosophers)\
	&& ((philo + k)->meals_eaten == meals))
	{
		if (k == philo->data->number_of_philosophers)
		{
			pthread_mutex_unlock(&philo->data->meals_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (0);
}

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
	int				meals;

	pthread_mutex_lock(&philo->data->meals_mutex);
	meals = philo->data->number_of_meals;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->data->meals_mutex);
		if (check_meals(philo, meals))
		{
			pthread_mutex_unlock(&philo->data->meals_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meals_mutex);
		if (monitor_death(philo))
			break ;
	}
}

void	initialize_philo(t_philo *philo, t_data *data, t_table *table)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		(philo + i)->philo_id = i + 1;
		(philo + i)->left_fork = 0;
		(philo + i)->right_fork = 0;
		(philo + i)->meals_eaten = 0;
		(philo + i)->last_meal = get_time();
		table->fork_id[i] = i;
		(philo + i)->data = data;
		(philo + i)->table = table;
		mutex_initialiser(philo);
		if (pthread_mutex_init((philo + i)->table->fork_mutex + i, NULL) == -1)
			return (str_fd("fork_mutex failed\n", 2), (void)NULL);
	}
	thread_create(philo);
}
