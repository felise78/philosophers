/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:33:13 by hemottu           #+#    #+#             */
/*   Updated: 2023/07/28 14:36:51 by hemottu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

enum {
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

typedef struct s_arg	t_arg;

typedef struct s_philo
{
	int				id;
	int				nb_of_meals;
	int				ate_all;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_arg			*arg;
}	t_philo;

struct s_arg
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_each_philo_eat;
	int				died;
	int				all_ate;
	long long		start;
	pthread_mutex_t	write;
	pthread_mutex_t	eating;
	pthread_mutex_t	dead;
	t_philo			*philo;
};

void		ft_put_error(char *str);
void		ft_init_mutex(t_arg *arg);
void		ft_create_threads(t_arg *arg);
void		*ft_routine(void *ptr);
void		ft_close_threads(t_arg *arg);
void		ft_destroy_mutex(t_arg *arg);
void		ft_write(t_philo *philo, int action);
void		ft_eat(t_philo *philo);
void		ft_sleep_think(t_philo *philo);
void		ft_monitoring(t_arg *arg);
void		ft_exit(t_arg *arg);
void		*ft_one_philo(void *ptr);
void		ft_usleep(long long time_in_ms);
int			ft_atoi(char *str);
int			ft_parse_digit(char **av);
int			ft_is_space(char c);
int			ft_is_digit(char c);
int			ft_strlen(char *str);
int			ft_take_forks(t_philo *philo);
long long	ft_get_time(void);

#endif
