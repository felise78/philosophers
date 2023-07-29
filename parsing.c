/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:29:41 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/28 14:03:39 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

int	ft_check_overflow(char *str)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb * sign > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 12)
			return (0);
		j = 0;
		while (av[i][j])
		{
			if (ft_is_digit(av[i][j]) == 0)
				return (0);
			j++;
		}
		if (ft_check_overflow(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (str[i])
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (value);
}
