/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:40:22 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/22 15:48:54 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg(":error with gettimeofday func\n");
	return (time.tv_sec * (1000) + (time.tv_usec / (1000)));
}

void	ft_usleep(long usec, t_dinner *dn)
{
	long	start;

	start = get_time();
	while ((get_value(&dn->dead, &dn->stop_dinner) == 0)
		&& (get_time() - start) < usec)
		usleep(500);
}

long	get_value_long(pthread_mutex_t *mutex, long *value)
{
	long	a;

	pthread_mutex_lock(mutex);
	a = *value;
	pthread_mutex_unlock(mutex);
	return (a);
}
