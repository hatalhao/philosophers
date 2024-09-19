#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct		s_data
{
	int				dead_philo;
	int				number_of_forks;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				exit_status;
	unsigned long	timestamp;
	pthread_mutex_t	exit_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	timestamp_mutex;
}					t_data;

typedef struct		s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				meals_eaten;
	int				*left_fork;
	int				*right_fork;
	unsigned long	last_meal;
	struct s_data	*data;
	struct s_table	*table;
	struct s_philo	*next;
}					t_philo;

typedef	struct		s_table
{
	int				*fork_id;
	pthread_mutex_t	*fork_mutex;
}					t_table;


int			check_args(char **av);
int			philo_init(char **av);
void		*philo_sequence(void *arg);
/*			few_utiles.c	*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		cleaner(t_philo *philo);
void		destroy_mutex(t_philo *philo);
size_t		ft_length(char const *str);
void		str_fd(char *s, int fd);
void		mutex_initialiser(t_philo *philo);


int			ft_atoi_prime(char const *nptr);
pthread_t	*assignment(pthread_t *philo, t_data *data);

/*		philo_state.c	*/
// void	is_eating(t_philo *philo);
int		check_death(t_philo *philo);
void	print(t_philo *philo, char *s);
void	took_fork(t_philo *philo);
// void	philo_died(t_philo *philo);

/*		philo_helpers.c	*/
void	ft_usleep(unsigned long time);
void	initialize_philo(t_philo *philo, t_data *data, t_table *table);
void	monitor(t_philo *philo);
long	get_time(void);

#endif