/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:31:01 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/21 21:12:03 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
}

void	sleeping(t_philo *philo, char *s)
{
	if (!ft_strncmp(s, "sleep", 5))
		ft_usleep (philo->data->time_to_sleep);
	else if (!ft_strncmp(s, "eat", 3))
	{
		pthread_mutex_lock(&philo->data->meals_mutex);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->data->meals_mutex);
		ft_usleep (philo->data->time_to_eat);
	}
	else if (!ft_strncmp(s, "think", 5))
		ft_usleep(1);
}

void	print(t_philo *philo, char *s)
{
	long	time_to_print;

	if (check_death(philo))
		return ;
	time_to_print = get_time() - philo->data->timestamp;
	if (!ft_strncmp(s, "die", 3) || !ft_strncmp(s, "meal", 4))
	{
		if (!ft_strncmp(s, "die", 3))
			printf("%ld %i has died\n", time_to_print, philo->philo_id);
		else
			printf("Minimum meals is reached\n");
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->dead_philo = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	else if (!ft_strncmp(s, "fork", 4))
		printf("%ld %i has taken a fork\n", time_to_print, philo->philo_id);
	else
		printf("%ld %i is %sing\n", time_to_print, philo->philo_id, s);
	sleeping(philo, s);
}

void	took_fork(t_philo *philo)
{
	if (check_death(philo))
		return ;
	if (philo->philo_id == philo->data->philo_count)
	{
		pthread_mutex_lock(&philo->data->fork_mutex \
		[philo->philo_id % philo->data->philo_count]);
		print(philo, "fork");
		pthread_mutex_lock(&philo->data->fork_mutex[philo->philo_id - 1]);
		print(philo, "fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork_mutex[philo->philo_id - 1]);
		print(philo, "fork");
		pthread_mutex_lock(&philo->data->fork_mutex \
		[philo->philo_id % philo->data->philo_count]);
		print(philo, "fork");
	}
	print(philo, "eat");
	update_last_meal(philo);
	pthread_mutex_unlock(&philo->data->fork_mutex \
	[philo->philo_id % philo->data->philo_count]);
	pthread_mutex_unlock(&philo->data->fork_mutex[philo->philo_id - 1]);
	print(philo, "sleep");
}
