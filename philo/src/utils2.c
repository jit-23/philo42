/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-jesu <fde-jesu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:49:00 by fde-jesu          #+#    #+#             */
/*   Updated: 2024/05/23 05:52:27 by fde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_msg(char *msm)
{
	int	i;

	i = -1;
	while (msm[++i])
		write(2, &msm[i], 1);
	return (1);
}

int	is_number(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_str_search(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_number(str[i]))
			return (1);
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	*s_malloc(size_t bts)
{
	void	*a;

	a = malloc(bts);
	if (!a)
		error_msg(":error allocating for malloc\n");
	return (a);
}
