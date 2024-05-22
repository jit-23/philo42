/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:14:40 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/22 17:01:34 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	alive(t_philo *ph)
{
	long	starving_ms;
	long	last_m_eaten;

	pthread_mutex_lock(&ph->meal);
	last_m_eaten = ph->last_meal_eaten;
	pthread_mutex_unlock(&ph->meal);
	if (get_value(&ph->dn->read, &ph->philo_full))
		return (1);
	starving_ms = get_time() - last_m_eaten;
	if (starving_ms >= ph->dn->time_to_die)
		return (0);
	return (1);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_philo	*monitor;

	monitor = (t_philo *)arg;
	while (get_value(&monitor->dn->read, &monitor->dn->dinner_ready) == 0)
		;
	while (get_value(&monitor->dn->dead, &monitor->dn->stop_dinner) != 1)
	{
		i = -1;
		while (++i < monitor->dn->n_phil && (get_value(&monitor->dn->dead,
					&monitor->dn->stop_dinner) != 1))
		{
			if (!alive(&monitor->dn->philo[i]))
			{
				set_value(&monitor->dn->dead, &monitor->dn->stop_dinner, 1);
				write_action(&monitor->dn->philo[i], "died");
				break ;
			}
		}
		if (get_value(&monitor->dn->dead, &monitor->dn->stop_dinner) == 1)
			break ;
	}
	return (0);
}

void	create_threads(t_dinner *dn)
{
	int		i;
	t_philo	*ph;

	ph = dn->philo;
	i = -1;
	if (ph->dn->n_phil > 1)
		if (pthread_create(&ph->dn->monitor->thread_id, NULL, &monitor_routine,
				ph->dn->monitor) != 0)
			error_msg("error with pthread_create function:");
	while (++i < ph->dn->n_phil)
		if (pthread_create(&ph[i].thread_id, NULL, routine, &ph[i]) != 0)
			error_msg("error with pthread_create function!");
	ph->dn->start_dinner_time = get_time();
	set_value(&dn->read, &dn->dinner_ready, 1);
	i = -1;
	while (++i < ph->dn->n_phil)
		if (pthread_join(ph[i].thread_id, NULL) != 0)
			error_msg("PHILO error with pthread_join function:");
	set_value(&dn->dead, &ph->dn->stop_dinner, 1);
	if (pthread_join(ph->dn->monitor->thread_id, NULL) != 0)
		error_msg("error with pthread_join function:");
	return ;
}

void	write_action(t_philo *ph, char *s)
{
	long	time_ms;

	if (get_value(&ph->dn->dead, &ph->dn->stop_dinner) == 1 && ft_strncmp(s,
			"died", sizeof("died")) != 0)
		return ;
	time_ms = get_time() - ph->dn->start_dinner_time;
	pthread_mutex_lock(&ph->dn->writing);
	printf("%ld %d %s\n", time_ms, ph->philo_id, s);
	pthread_mutex_unlock(&ph->dn->writing);
}

void	set_dinner_start(pthread_mutex_t *m, long *d, long s)
{
	pthread_mutex_lock(m);
	*d = s;
	pthread_mutex_unlock(m);
}
