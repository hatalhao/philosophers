#include "../includes/philosophers.h"

void	*philo_sequence()
{

}

pthread_t	*assignment(pthread_t *philo, t_data *data)
{
	philo = malloc (sizeof(*philo) * data->number_of_philosophers);
	if (!philo)
		return ;
}

void	philo_init(t_data *data)
{
	int	i;
	pthread_t	*philo;

	i = -1;
	philo = assignment(philo, data);
	while (++i < data->number_of_philosophers)
		pthread_create(philo + i, NULL, &philo_sequence, NULL);
	

}
