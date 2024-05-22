/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:43:29 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/22 16:26:24 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_meals(char *nbr, char *meals)
{
	int	i;
	int	j;
	int	result;

	i = -1;
	j = 0;
	while (meals[++i])
	{
		if (meals[i] == '[' || meals[i] == ']')
			continue ;
		else
			nbr[j++] = meals[i];
	}
	nbr[j] = '\0';
	result = ft_atoll(nbr);
	free(nbr);
	return (result);
}

int	check_args(int ac, char **stats)
{
	int			i;
	long long	x;

	i = 1;
	while (i < 5)
	{
		if (ft_str_search(stats[i]))
			return (1);
		x = ft_atoll(stats[i]);
		if (x < 0 || x > 2147483647)
			return (1);
		i++;
	}
	if (ac == 6)
	{
		x = check_meal_val(stats[5]);
		if (x < 0 || x > 2147483647)
			return (1);
	}
	return (0);
}

int	check_meal_val(char *meals)
{
	int		i;
	int		j;
	char	*nbr;

	i = -1;
	j = 0;
	while (meals[++i])
	{
		if (meals[i] == '[' || meals[i] == ']')
			i++;
		else
			j++;
	}
	nbr = (char *)malloc(sizeof(char) * j + 1);
	return (ft_meals(nbr, meals));
}
