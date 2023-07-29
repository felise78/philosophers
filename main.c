/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:56:57 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/28 12:48:59 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_init_arguments(char **av, t_arg *arg)
{
	arg->start = ft_get_time();
	if (arg->start == 0)
	{
		ft_put_error("Error with the time intialization\n");
		return ;
	}
	arg->number_of_philosophers = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		arg->nb_each_philo_eat = ft_atoi(av[5]);
	else
		arg->nb_each_philo_eat = -1;
	arg->died = 0;
	arg->all_ate = 0;
}

void	ft_exit(t_arg *arg)
{
	ft_close_threads(arg);
	ft_destroy_mutex(arg);
	free(arg->philo);
}

int	main(int ac, char **av)
{
	t_arg	arg;

	if (ac != 5 && ac != 6)
		return (ft_put_error("Error with the number of arguments\n"), 2);
	if (ft_parse_digit(av) == 0)
		return (ft_put_error("Error with the arguments\n"), 2);
	ft_init_arguments(av, &arg);
	if (arg.number_of_philosophers == 0 || arg.time_to_die == 0
		|| arg.time_to_eat == 0 || arg.time_to_sleep == 0)
		return (ft_put_error("Error with the parameters\n"), 2);
	if (av[5] && arg.nb_each_philo_eat == 0)
		return (ft_put_error("Error, last parameter can not be null"), 2);
	arg.philo = malloc(sizeof(t_philo) * arg.number_of_philosophers);
	if (!arg.philo)
		return (ft_put_error("Error with memory allocation\n"), 2);
	ft_init_mutex(&arg);
	ft_create_threads(&arg);
	ft_monitoring(&arg);
	ft_exit(&arg);
	return (0);
}
