/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:23:59 by skock             #+#    #+#             */
/*   Updated: 2025/03/07 14:55:40 by skock            ###   ########.fr       */
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
	pthread_t		thread;
	int				id;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				last_meal;
	int				nb_meal;
	int				nb_philo;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	nb_meal_mutex;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	dying_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	int				nb_philosoph;
	int				time_start;
	bool			meal;
	bool			is_dead;
	bool			finish_eating;
	t_philo			*philo;
}					t_table;

// PARSING
int		ft_atoi(const char *str);
int		verif_arg(int ac, char **av);
int		is_digit(char *arg);
// ROUTINE
int		eat_routine(t_philo *philo);
void	solo_routine(t_philo *philo);
void	*philo_routine(void *arg);
void	death_routine(t_table *table);
// ROUTINE_UTILS
int		verif_is_dead(t_philo *philo);
int		dying(t_philo *philo);
void	drop_fork(t_philo *philo);
int		take_fork(t_philo *philo);
// TIME
int		get_each_ms(void);
int		ft_usleep(int time, t_philo *philo);
// PRINT
void	print(t_philo *philo, char *msg);

#endif