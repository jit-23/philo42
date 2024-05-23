/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:04:50 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/23 05:53:09 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo	t_philo;
typedef struct s_dinner	t_dinner;

struct s_philo
{
	int				philo_id;
	int				n_meals_eaten;
	int				philo_full;
	long			last_meal_eaten;
	int				first_fork;
	int				second_fork;
	pthread_t		thread_id;
	t_dinner		*dn;
	pthread_mutex_t	meal;
};

struct s_dinner
{
	int				n_phil;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	int				n_meals;

	long			start_dinner_time;
	int				stop_dinner;
	int				dinner_ready;
	int				philos_done_eating;
	t_philo			*monitor;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	writing;
	pthread_mutex_t	dead;
	pthread_mutex_t	read;
};

int				ft_meals(char *nbr, char *meals);
int				check_args(int ac, char **stats);
int				check_meal_val(char *meals);
int				ft_str_search( char *str);

void			init_default_values(t_dinner *dn);
void			init_mutex(t_dinner *dn);
void			init_forks(t_philo *philo);

long			get_time(void);
void			ft_usleep(long usec, t_dinner *dn);
int				get_value(pthread_mutex_t *mutex, int *value);
int				ft_atoi(char *nptr);
void			*s_malloc(size_t bts);
long long int	ft_atoll(char *nbr);
int				error_msg(char *msm);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*routine(void *arg);
void			create_threads(t_dinner *dn);
void			init_table(t_dinner *dn, char **stats);

void			set_value(pthread_mutex_t *mutex, int *dest, int src);
void			set_value_long(pthread_mutex_t *mutex, long *dest, long src);
void			write_action(t_philo *ph, char *s);

void			lone_philo(t_philo *ph);
void			de_syncronize(t_philo *ph);
void			think(t_philo *ph);
void			eat(t_philo *ph);
int				is_number(int c);
int				ft_meals_search(char *str);

long			get_value_long(pthread_mutex_t *mutex, long *value);
void			de_syncronize(t_philo *ph);
void			set_dinner_start(pthread_mutex_t *m, long *d, long s);

#endif