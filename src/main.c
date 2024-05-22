/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:00:55 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/22 16:53:54 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		philo->first_fork = philo->philo_id - 1;
		philo->second_fork = philo->philo_id % philo->dn->n_phil;
	}
	else
	{
		philo->second_fork = philo->philo_id - 1;
		philo->first_fork = philo->philo_id % philo->dn->n_phil;
	}
}

static void	delete_all(t_dinner *dn)
{
	int	i;

	i = -1;
	while (++i < dn->n_phil)
		pthread_mutex_destroy(&dn->philo[i].meal);
	i = -1;
	while (++i < dn->n_phil)
		pthread_mutex_destroy(&dn->fork[i]);
	free(dn->philo);
	free(dn->fork);
	free(dn->monitor);
	pthread_mutex_destroy(&dn->writing);
	pthread_mutex_destroy(&dn->dead);
	pthread_mutex_destroy(&dn->read);
}

int	main(int ac, char *av[])
{
	t_dinner	dinner;

	if (ac != 5 && ac != 6)
		return (error_msg("wrong nbr of args\n"), 1);
	if (check_args(ac, av))
		return (error_msg("wrong type of args\n"), 1);
	init_table(&dinner, av);
	create_threads(&dinner);
	delete_all(&dinner);
	return (0);
}
