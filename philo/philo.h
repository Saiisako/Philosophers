/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:23:59 by skock             #+#    #+#             */
/*   Updated: 2025/02/18 14:43:12 by skock            ###   ########.fr       */
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
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*simulation_running_mutex;
	pthread_mutex_t	*last_meal_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_to_eat;
	long long		last_meal;
	long long		start_time;
	int				nb_meal;
	bool			is_dead;
	int				simulation_running;
	int				nb_philo;
	bool			is_eating;
	bool			hold_fork;
} t_philo;

typedef struct s_table
{
	int				nb_philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simulation_running_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
	int				nb_forks;
	int				simulation_running;
	int				nb_finish_eating;
	t_philo			*philo;
}					t_table;

int		ft_atoi(const char *str);
void	fill_struc(t_philo *philo, int ac, char **av);

#endif