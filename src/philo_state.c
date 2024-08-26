#include "../includes/philo.h"

void	took_fork(t_philo *philo)
{
	philo->data->timestamp += 5;
	// printf("%i has taken a fork\n", philo->philo_id);
	printf("%i %d has taken a fork\n", philo->philo_id, philo->data->timestamp);
	// usleep (data->time_to_sleep * 1000);
}

void	is_eating(t_philo *philo)
{
	
	printf("%i %d is eating\n", philo->philo_id, philo->data->timestamp);
	// usleep (data->time_to_eat * 1000);
}

void	is_sleeping(t_philo *philo)
{

	printf("%i %d is sleeping\n", philo->philo_id, philo->data->timestamp);
	// usleep (data->time_to_sleep * 1000);
}

void	is_thinking(t_philo *philo)
{

	printf("%i %d is thinking\n", philo->philo_id, philo->data->timestamp);
	// usleep (data->time_to_die * 1000);
}

void	philo_died(t_philo *philo)
{
	// add a mutex that will lock the timestamp before exiting
	printf("%i %d has died\n", philo->philo_id, philo->data->timestamp);
	philo->data->dead_philo = 1;
}
