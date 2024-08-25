#include "../includes/philo.h"

void	took_fork(t_philo *philo, t_data *data)
{
	
	printf("%i %d has taken a fork", philo->philo_id, data->timestamp);
	// usleep (data->time_to_sleep * 1000);
}

void	is_eating(t_philo *philo, t_data *data)
{
	printf("%i %d is eating", philo->philo_id, data->timestamp);
	usleep (data->time_to_eat * 1000);
}

void	is_sleeping(t_philo *philo, t_data *data)
{
	printf("%i %d is sleeping", philo->philo_id, data->timestamp);
	usleep (data->time_to_sleep * 1000);
}

void	is_thinking(t_philo *philo, t_data *data)
{
	printf("%i %d is thinking", philo->philo_id, data->timestamp);
	usleep (data->time_to_die * 1000);
}

void	philo_died(t_philo *philo, t_data *data)
{
	printf("%i %d has taken a fork", philo->philo_id, data->timestamp);
	philo->data->dead_philo = 1;
}
