/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 00:57:33 by hatalhao          #+#    #+#             */
/*   Updated: 2024/09/21 21:21:33 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				dead_philo;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				*fork_id;
	unsigned long	timestamp;
	pthread_mutex_t	exit_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	timestamp_mutex;
	pthread_mutex_t	*fork_mutex;
}					t_data;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				meals_eaten;
	unsigned long	last_meal;
	struct s_data	*data;
}					t_philo;

/*			utils.c	*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		cleaner(t_philo *philo);
void		destroy_mutex(t_philo *philo);
size_t		ft_length(char const *str);
void		str_fd(char *s, int fd);
void		mutex_initialiser(t_philo *philo);

/*			assignments.c		*/
int			philo_init(char **av);
t_data		*data_init(t_data *data, char **av);
pthread_t	*assignment(pthread_t *philo, t_data *data);
void		initialize_philo(t_philo *philo, t_data *data);

/*			parse_args.c		*/
int			is_num(char *s);
int			off_bound(long nb);
int			check_args(char **av);
int			ft_atoi_prime(char const *nptr);

/*			philo_state.c	*/
int			check_death(t_philo *philo);
void		print(t_philo *philo, char *s);
void		took_fork(t_philo *philo);
void		sleeping(t_philo *philo, char *s);


/*			timers.c		*/
long		get_time(void);
void		ft_usleep(unsigned long time);

/*			monitors.c		*/
void		monitor(t_philo *philo);
int			check_death(t_philo *philo);
int			monitor_death(t_philo *philo);
int			check_meals(t_philo *philo, int meals);

/*			threading.c			*/
void		*philo_sequence(void *arg);
void		thread_create(t_philo *philo);
void		join_threads(t_philo *philo);

#endif
