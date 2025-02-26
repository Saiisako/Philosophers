/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:23:59 by skock             #+#    #+#             */
/*   Updated: 2025/02/26 16:49:00 by skock            ###   ########.fr       */
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
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			have_to_eat;
	long long		last_meal;
	long long		start_time;
	int				nb_meal;
	int				simulation_running;
	int				nb_philo;
	bool			hold_fork;
	bool			is_eating;
	pthread_mutex_t	is_eating_mutex;
	struct s_table *table;
}					t_philo;

typedef struct s_table
{
	int				nb_philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	nb_meal_mutex;
	int				simulation_running;
	bool			is_dead;
	pthread_mutex_t	is_dead_mutex;
	t_philo			*philo;
}					t_table;

int		ft_atoi(const char *str);
int		verif_arg(int ac, char **av);


#endif