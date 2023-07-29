/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:48:28 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/28 17:50:46 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_write(t_philo *philo, int action)
{
	static int	is_dead = 0;
	int			time;

	time = ft_get_time() - philo->arg->start;
	pthread_mutex_lock(&philo->arg->write);
	if (!is_dead)
	{
		printf("%d ", time);
		if (action == FORK)
			printf("%d has taken a fork\n", philo->id);
		if (action == EAT)
			printf("%d is eating\n", philo->id);
		else if (action == SLEEP)
			printf("%d is sleeping\n", philo->id);
		else if (action == THINK)
			printf("%d is thinking\n", philo->id);
		else if (action == DEAD)
		{
			printf("%d is dead\n", philo->id);
			is_dead = 1;
		}
	}
	pthread_mutex_unlock(&philo->arg->write);
}
