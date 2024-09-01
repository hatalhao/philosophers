#include "../includes/philo.h"

void	took_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->table->fork_mutex + philo->philo_id - 1) == 0)
		philo->right_fork = philo->table->fork_id + philo->philo_id - 1;
	printf("%ld %i has taken a fork\n", get_time() - philo->data->timestamp, philo->philo_id);
	
	if (pthread_mutex_lock(philo->table->fork_mutex + philo->philo_id) == 0)
		philo->left_fork = philo->table->fork_id + philo->philo_id;
	printf("%ld %i has taken a fork\n", get_time() - philo->data->timestamp, philo->philo_id);
	
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	
	is_eating(philo);
	
	if (pthread_mutex_unlock(philo->table->fork_mutex + philo->philo_id - 1) == 0)
		philo->right_fork = 0;
	if (pthread_mutex_unlock(philo->table->fork_mutex + philo->philo_id) == 0)
		philo->left_fork = 0;
	is_sleeping(philo);
}

void	is_eating(t_philo *philo)
{
	if (philo->data->number_of_meals && philo->meals_eaten == philo->data->number_of_meals)
		return ;
	printf("%ld %i is eating\n", get_time() - philo->data->timestamp, philo->philo_id);
	usleep (philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->data->meals_mutex);
}

void	is_sleeping(t_philo *philo)
{
	printf("%ld %i is sleeping\n", get_time() - philo->data->timestamp, philo->philo_id);
	usleep (philo->data->time_to_sleep * 1000);
}

void	is_thinking(t_philo *philo)
{
	printf("%ld %i is thinking\n", get_time() - philo->data->timestamp, philo->philo_id);
}

void	philo_died(t_philo *philo)
{
	printf("%ld %i has died\n", get_time() - philo->data->timestamp, philo->philo_id);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->dead_philo = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
}
