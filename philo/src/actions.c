/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:28:44 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/23 05:16:14 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->dn->fork[ph->first_fork]);
	write_action(ph, "has taken a fork");
	pthread_mutex_lock(&ph->dn->fork[ph->second_fork]);
	write_action(ph, "has taken a fork");
	write_action(ph, "is eating");
	set_value_long(&ph->meal, &ph->last_meal_eaten, get_time());
	ph->n_meals_eaten++;
	ft_usleep(ph->dn->time_to_eat, ph->dn);
	if (ph->n_meals_eaten == ph->dn->n_meals)
		set_value(&ph->dn->read, &ph->philo_full, 1);
	pthread_mutex_unlock(&ph->dn->fork[ph->second_fork]);
	pthread_mutex_unlock(&ph->dn->fork[ph->first_fork]);
}

void	think(t_philo *ph)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (get_value(&ph->dn->dead, &ph->dn->stop_dinner) == 1)
		return ;
	write_action(ph, "is thinking");
	if (ph->dn->n_phil % 2 == 0)
		return ;
	t_eat = ph->dn->time_to_eat;
	t_sleep = ph->dn->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		return ;
	ft_usleep((t_think * 0.3), ph->dn);
}

void	de_syncronize(t_philo *ph)
{
	if (ph->dn->n_phil % 2 == 0)
	{
		if (ph->philo_id % 2 == 0)
			ft_usleep(1, ph->dn);
	}
	else
		if (ph->philo_id % 2 == 1)
			think(ph);
}

void	lone_philo(t_philo *ph)
{
	pthread_mutex_lock(&ph->dn->fork[ph->first_fork]);
	write_action(ph, "has taken a fork");
	ft_usleep(ph->dn->time_to_die, ph->dn);
	write_action(ph, "has died");
	pthread_mutex_unlock(&ph->dn->fork[ph->first_fork]);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (get_value(&ph->dn->read, &ph->dn->dinner_ready) == 0)
		;
	if (ph->dn->n_phil == 1)
	{
		lone_philo(ph);
		return (0);
	}
	set_dinner_start(&ph->meal, &ph->last_meal_eaten, get_time());
	de_syncronize(ph);
	while (get_value(&ph->dn->dead, &ph->dn->stop_dinner) != 1
		&& ph->philo_full != 1)
	{
		eat(ph);
		write_action(ph, "is sleeping");
		ft_usleep(ph->dn->time_to_sleep, ph->dn);
		think(ph);
	}
	return (0);
}
