#include "../includes/philo.h"

void	took_fork(t_philo *philo)
{
	philo->data->timestamp += 5;
	if (pthread_mutex_lock(philo->table->fork_mutex + philo->philo_id - 1) == 0)
		philo->right_fork = philo->table->fork_id + philo->philo_id - 1;
	printf("%i %d has taken the right fork\n", philo->philo_id, philo->data->timestamp);
	if (pthread_mutex_lock(philo->table->fork_mutex + philo->philo_id) == 0)
		philo->left_fork = philo->table->fork_id + philo->philo_id;
	printf("%i %d has taken the left fork\n", philo->philo_id, philo->data->timestamp);
	is_eating(philo);
	is_sleeping(philo);
	pthread_mutex_unlock(philo->table->fork_mutex);
	philo->right_fork = 0;
	philo->left_fork = 0;
}

void	is_eating(t_philo *philo)
{
	if (philo->meals_eaten == philo->data->number_of_meals)
		return ;
	philo->last_meal = philo->data->timestamp;
	printf("%i %d is eating\n", philo->philo_id, philo->data->timestamp);
	usleep (philo->data->time_to_eat * 1000);
	philo->meals_eaten += 1;
}

void	is_sleeping(t_philo *philo)
{

	printf("%i %d is sleeping\n", philo->philo_id, philo->data->timestamp);
	usleep (philo->data->time_to_sleep * 1000);
}

void	is_thinking(t_philo *philo)
{

	printf("%i %d is thinking\n", philo->philo_id, philo->data->timestamp);
	usleep(100);
}

void	philo_died(t_philo *philo)
{
	// add a mutex that will lock the timestamp before exiting
	if (philo->data->time_to_die > philo->data->timestamp - philo->last_meal)
		return ;
	printf("%i %d has died\n", philo->philo_id, philo->data->timestamp);
	philo->data->dead_philo = 1;
}
