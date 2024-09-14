#include "../includes/philo.h"

void	destroy_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->death_mutex);
	pthread_mutex_destroy(&philo->data->exit_mutex);
	pthread_mutex_destroy(&philo->data->last_meal_mutex);
	pthread_mutex_destroy(&philo->data->timestamp_mutex);
	pthread_mutex_destroy(&philo->data->meals_mutex);
	pthread_mutex_destroy(philo->table->fork_mutex);
}

void	mutex_initialiser(t_philo *philo)
{
	pthread_mutex_init(&philo->data->meals_mutex, NULL);
	pthread_mutex_init(&philo->data->exit_mutex, NULL);
	pthread_mutex_init(&philo->data->last_meal_mutex, NULL);
	pthread_mutex_init(&philo->data->death_mutex, NULL);
}

size_t	ft_length(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	str_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_length(s));
}
