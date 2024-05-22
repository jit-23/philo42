/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:46:34 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/22 16:48:27 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_mon(t_dinner *dn)
{
	dn->monitor = s_malloc(sizeof(t_philo));
	dn->monitor->dn = dn;
	pthread_mutex_init(&dn->monitor->meal, NULL);
}

void	init_table(t_dinner *dn, char **stats)
{
	dn->n_phil = ft_atoi(stats[1]);
	dn->time_to_die = ft_atoi(stats[2]);
	dn->time_to_eat = ft_atoi(stats[3]);
	dn->time_to_sleep = ft_atoi(stats[4]);
	if (stats[5])
		dn->n_meals = check_meal_val(stats[5]);
	else
		dn->n_meals = -1;
	init_default_values(dn);
}

void	init_default_values(t_dinner *dn)
{
	int		i;
	t_philo	*ph;

	i = -1;
	dn->philo = s_malloc(sizeof(t_philo) * dn->n_phil);
	dn->fork = s_malloc(sizeof(pthread_mutex_t) * dn->n_phil);
	dn->start_dinner_time = get_time();
	dn->dinner_ready = 0;
	dn->philos_done_eating = 0;
	init_mutex(dn);
	init_mon(dn);
	while (++i < dn->n_phil)
	{
		ph = &dn->philo[i];
		ph->dn = dn;
		ph->last_meal_eaten = get_time();
		ph->dn = dn;
		ph->n_meals_eaten = 0;
		ph->philo_full = 0;
		ph->philo_id = i + 1;
		init_forks(ph);
	}
}

void	init_mutex(t_dinner *dn)
{
	int	i;

	i = -1;
	while (++i < dn->n_phil)
	{
		pthread_mutex_init(&dn->philo[i].meal, NULL);
		pthread_mutex_init(&dn->fork[i], NULL);
	}
	pthread_mutex_init(&dn->writing, NULL);
	pthread_mutex_init(&dn->dead, NULL);
	pthread_mutex_init(&dn->read, NULL);
}
