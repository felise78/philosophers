/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:48:11 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/28 17:38:46 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	ft_eat(t_philo *philo)
{
	ft_write(philo, EAT);
	pthread_mutex_lock(&philo->arg->eating);
	philo->nb_of_meals++;
	if (philo->arg->nb_each_philo_eat != -1
		&& (philo->nb_of_meals == philo->arg->nb_each_philo_eat))
		philo->ate_all = 1;
	philo->last_meal = ft_get_time() - philo->arg->start;
	pthread_mutex_unlock(&philo->arg->eating);
	ft_usleep(philo->arg->time_to_eat);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

int	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->l_fork);
		ft_write(philo, FORK);
		if (philo->arg->number_of_philosophers == 1)
		{
			pthread_mutex_unlock(&philo->l_fork);
			ft_usleep(philo->arg->time_to_die);
			philo->arg->died = 1;
			ft_write(philo, DEAD);
			return (0);
		}
		pthread_mutex_lock(philo->r_fork);
		ft_write(philo, FORK);
		return (1);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_write(philo, FORK);
		pthread_mutex_lock(&philo->l_fork);
		ft_write(philo, FORK);
		return (1);
	}
}

void	ft_sleep_think(t_philo *philo)
{
	ft_write(philo, SLEEP);
	ft_usleep(philo->arg->time_to_sleep);
	ft_write(philo, THINK);
	if (philo->arg->time_to_die > (philo->arg->time_to_sleep * 2
			+ philo->arg->time_to_eat))
		ft_usleep(philo->arg->time_to_sleep);
}
