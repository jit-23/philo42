/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:40:08 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/22 16:51:10 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long int	ft_atoll(char *nbr)
{
	int				i;
	int				signal;
	long long int	result;

	i = 0;
	signal = 1;
	result = 0;
	if ((nbr[i] == 32 || (nbr[i] >= 7 && nbr[i] <= 13)) && nbr)
		i++;
	if (nbr[i] == '-')
	{
		signal = -1;
		i++;
	}
	if (nbr[i] < '0' && nbr[i] > '9')
	{
		error_msg(":invalid type of arg");
		exit(1);
	}
	while (nbr[i])
	{
		result = result * 10 + nbr[i++] - '0';
	}
	return (result * signal);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sinal;
	int	result;

	result = 0;
	sinal = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sinal = -sinal;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
	{
		error_msg(":invalid type of arg\n");
		exit(1);
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (sinal * result);
}

void	set_value(pthread_mutex_t *mutex, int *dest, int src)
{
	pthread_mutex_lock(mutex);
	*dest = src;
	pthread_mutex_unlock(mutex);
}

void	set_value_long(pthread_mutex_t *mutex, long *dest, long src)
{
	pthread_mutex_lock(mutex);
	*dest = src;
	pthread_mutex_unlock(mutex);
}

int	get_value(pthread_mutex_t *mutex, int *value)
{
	int	a;

	pthread_mutex_lock(mutex);
	a = *value;
	pthread_mutex_unlock(mutex);
	return (a);
}
