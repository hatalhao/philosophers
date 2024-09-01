#include "../includes/philo.h"

void	took_fork(t_philo *philo)
{
	// get_time();
	if (pthread_mutex_lock(philo->table->fork_mutex + philo->philo_id - 1) == 0)
		philo->right_fork = philo->table->fork_id + philo->philo_id - 1;
	printf("%i %ld has taken the right fork\n", philo->philo_id, get_time() - philo->data->timestamp);
	if (pthread_mutex_lock(philo->table->fork_mutex + philo->philo_id) == 0)
		philo->left_fork = philo->table->fork_id + philo->philo_id;
	printf("%i %ld has taken the left fork\n", philo->philo_id, get_time() - philo->data->timestamp);
	if (pthread_mutex_lock(&philo->data->exec_mutex) == 0)
		philo->last_meal = get_time();
	if (pthread_mutex_unlock(&philo->data->exec_mutex) == 0)
		;
	is_eating(philo);
	if (pthread_mutex_unlock(philo->table->fork_mutex + philo->philo_id - 1) == 0)
		philo->right_fork = 0;
	if (pthread_mutex_unlock(philo->table->fork_mutex + philo->philo_id) == 0)
		philo->left_fork = 0;
	// get_time();
	is_sleeping(philo);
}

void	is_eating(t_philo *philo)
{
	if (philo->data->number_of_meals && philo->meals_eaten == philo->data->number_of_meals)
		return ;
	printf("%i %ld is eating\n", philo->philo_id, get_time() - philo->data->timestamp);
	usleep (philo->data->time_to_eat * 1000);
	philo->meals_eaten += 1;
}

void	is_sleeping(t_philo *philo)
{
	printf("%i %ld is sleeping\n", philo->philo_id, get_time() - philo->data->timestamp);
	usleep (philo->data->time_to_sleep * 1000);
}

void	is_thinking(t_philo *philo)
{
	printf("%i %ld is thinking\n", philo->philo_id, get_time() - philo->data->timestamp);
}

void	philo_died(t_philo *philo)
{
	printf("%i %ld has died\n", philo->philo_id, get_time() - philo->data->timestamp);
	pthread_mutex_lock(&philo->data->timestamp_mutex);
	philo->data->dead_philo = 1;
	pthread_mutex_unlock(&philo->data->timestamp_mutex);
}
