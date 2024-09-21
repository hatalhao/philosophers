/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:52:40 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/21 01:08:28 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_philo)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	monitor_death(t_philo *philo)
{
	long	last_meal;
	int		k;
	int		meals;

	pthread_mutex_lock(&philo->data->meals_mutex);
	meals = philo->data->number_of_meals;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	k = -1;
	while (++k < philo->data->philo_count)
	{
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		last_meal = (unsigned long)(philo + k)->last_meal;
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		if ((long)(philo + k)->data->time_to_die <= (get_time() - last_meal))
			return (print(philo + k, "die"), 1);
		if (meals && check_meals(philo, meals))
			return (print(philo + k, "meal"), 1);
	}
	return (0);
}

int	check_meals(t_philo *philo, int meals)
{
	int	k;
	int	count;

	k = -1;
	count = philo->data->philo_count;
	pthread_mutex_lock(&philo->data->meals_mutex);
	while ((++k < count) && ((philo + k)->meals_eaten >= meals))
	{
		if (k == count - 1)
		{
			pthread_mutex_unlock(&philo->data->meals_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
	return (0);
}

void	monitor(t_philo *philo)
{
	while (1)
		if ((monitor_death(philo)))
			return ;
}
