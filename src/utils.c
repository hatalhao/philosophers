/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:52:23 by hatalhao          #+#    #+#             */
/*   Updated: 2024/10/04 22:36:58 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->death_mutex);
	pthread_mutex_destroy(&philo->data->last_meal_mutex);
	pthread_mutex_destroy(&philo->data->meals_mutex);
	pthread_mutex_destroy(philo->data->fork_mutex);
}

void	mutex_initialiser(t_philo *philo)
{
	pthread_mutex_init(&philo->data->meals_mutex, NULL);
	pthread_mutex_init(&philo->data->last_meal_mutex, NULL);
	pthread_mutex_init(&philo->data->death_mutex, NULL);
}

void	cleaner(t_philo *philo)
{
	destroy_mutex(philo);
	free (philo->data->fork_mutex);
	free (philo->data);
	free (philo);
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
