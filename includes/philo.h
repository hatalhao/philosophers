#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct	s_data
{
	int			dead_philo;
	int			number_of_forks;
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	int			timestamp;
	pthread_mutex_t	timestamp_mutex;
	int			start_exec;
	// struct s_philo	*philo;
}				t_data;

typedef struct		s_philo
{
	struct s_data	*data;
	struct s_table	*table;
	int				philo_id;
	int				left_fork;
	int				right_fork;
}					t_philo;

typedef	struct		s_table
{
	int				*fork;
	pthread_mutex_t	*fork_mutex;
}					t_table;


void		check_args(char **av);
void		philo_init(char **av);
void		*philo_sequence(void *arg);
void		mutex_lock_unlock(pthread_mutex_t *mutex, int *k);

/*		few_utiles.c	*/
size_t		ft_length(char const *str);
void		str_fd(char *s, int fd);

int			ft_atoi_prime(char const *nptr);
pthread_t	*assignment(pthread_t *philo, t_data *data);

#endif