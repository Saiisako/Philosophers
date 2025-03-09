/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:23:59 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 16:08:06 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_t		thread;
	pthread_mutex_t	last_eat_mutex;
	long			last_eat;
	pthread_mutex_t	meal_take_mutex;
	int				meal_take;
	int				id;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	pthread_mutex_t	is_dead_mutex;
	bool			is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_time_mutex;
	long			start_time;
	pthread_mutex_t	meal_max_mutex;
	int				meal_max;
	int				nb_philosoph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philo;
}					t_table;
// UTILS

int		ft_atoi(char *str);
long	get_time(void);
void	print_table(char *str, t_philo *philo);

// ORDERS

void	think(t_philo *philo);
void	sleeping(t_philo *philo);
void	eat(t_philo *philo, int i);
void	go_eat(t_philo *philo);

// ROUTINES

void	one_philo(t_philo *philo, t_table *table);
void	*routine(void *arg);
void	*monitoring(void *arg);
void	limited_routine(t_philo *philo);
void	unlimited_routine(t_philo *philo);
void	*solo_routine(void *arg);

// ROUTINES UTILS

bool	check_thread(t_philo *philo);
bool	someone_dead(t_philo *philo);

// INITIALISE

void	init_philo(t_philo *philo, t_table *table, pthread_t monitoring_t,
			int i);
void	init_fork(t_table **table, t_philo *philo, int i);
t_table	*init_table(t_table *table, int ac, char **av, t_philo *philo);

// FREE

void	destroy_mutex(t_table *table, t_philo *philo);
void	free_all(t_philo *philo, t_table *table);

#endif