/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:55:39 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/29 18:18:13 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ft_create_threads(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		arg->philo[i].id = i + 1;
		arg->philo[i].arg = arg;
		arg->philo[i].ate_all = 0;
		if (arg->nb_each_philo_eat != -1)
			arg->philo[i].nb_of_meals = 0;
		arg->philo[i].last_meal = ft_get_time();
		if (pthread_create(&arg->philo[i].thread, NULL,
				ft_routine, &arg->philo[i]) != 0)
			return (ft_put_error("Error with thread initialization"));
		i++;
	}
}	

void	ft_check_death(t_arg *arg, int i)
{
	long long	time;

	pthread_mutex_lock(&(arg->dead));
	time = ft_get_time() - arg->start;
	if (time > (arg->philo[i].last_meal + arg->time_to_die))
	{
		ft_write(&(arg->philo[i]), DEAD);
		arg->died = 1;
	}
	pthread_mutex_unlock(&(arg->dead));
}

void	ft_monitoring(t_arg *arg)
{
	int			i;

	i = 0;
	while (!(arg->all_ate))
	{
		while (i < arg->number_of_philosophers && !(arg->died)
			&& !(arg->philo[i].ate_all))
		{
			ft_check_death(arg, i);
			i++;
		}
		if (arg->died)
			break ;
		i = 0;
		while (arg->nb_each_philo_eat && i < arg->number_of_philosophers
			&& arg->philo[i].ate_all)
			i++;
		if (i == arg->number_of_philosophers)
			arg->all_ate = 1;
		ft_usleep(1);
	}
}

void	*ft_routine(void *ptr)
{	
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		ft_usleep(philo->arg->time_to_eat / 10);
	while (!(philo->arg->died) && !(philo->arg->all_ate))
	{
		if (ft_take_forks(philo) == 0)
			break ;
		ft_eat(philo);
		if (philo->arg->nb_each_philo_eat && philo->arg->all_ate)
			break ;
		ft_sleep_think(philo);
	}
	return (NULL);
}

void	ft_close_threads(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		if (pthread_join(arg->philo[i].thread, NULL) != 0)
			return ;
		i++;
	}
}

// I need to sleep in the monitoring so that the CPU rests a little bit and 
// can do other things
// (I didn't work when I used valgrind without this little pause)
