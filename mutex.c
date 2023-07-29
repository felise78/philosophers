/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:49:07 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/29 13:12:41 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_mutex(t_arg *arg)
{
	int	i;

	if (pthread_mutex_init(&arg->write, NULL) != 0
		|| pthread_mutex_init(&arg->dead, NULL) != 0
		|| pthread_mutex_init(&arg->eating, NULL) != 0)
		return (ft_put_error("Error during mutex initialization\n"));
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		if (pthread_mutex_init(&arg->philo[i].l_fork, NULL) != 0)
			return (ft_put_error("Error during mutex initialization\n"));
		if (arg->number_of_philosophers == 1)
			return ;
		if (i == (arg->number_of_philosophers - 1))
			arg->philo[i].r_fork = &arg->philo[0].l_fork;
		else
			arg->philo[i].r_fork = &arg->philo[i + 1].l_fork;
		i++;
	}
}

void	ft_destroy_mutex(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&arg->philo[i].l_fork) != 0)
			return (ft_put_error("Error during mutex_destroy function\n"));
		i++;
	}
	if (pthread_mutex_destroy(&arg->write) != 0)
		return (ft_put_error("Error during mutex_destroy function\n"));
	if (pthread_mutex_destroy(&arg->eating) != 0)
		return (ft_put_error("Error during mutex_destroy function\n"));
	if (pthread_mutex_destroy(&arg->dead) != 0)
		return (ft_put_error("Error during mutex_destroy function\n"));
}
