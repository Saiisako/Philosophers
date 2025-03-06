/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:23:59 by skock             #+#    #+#             */
/*   Updated: 2025/03/05 18:18:26 by skock            ###   ########.fr       */
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
	pthread_mutex_t	is_eating_mutex;
	pthread_mutex_t	last_meal_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			have_to_eat;
	int				last_meal;
	int				nb_meal;
	int				nb_philo;
	bool			is_eating;
	struct s_table *table;
}					t_philo;

typedef struct s_table
{
	int				nb_philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	nb_meal_mutex;
	bool			meal;
	int				time_start;
	bool			is_dead;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	dying_mutex;
	pthread_mutex_t print_mutex;
	t_philo			*philo;
}					t_table;

int		ft_atoi(const char *str);
int		verif_arg(int ac, char **av);
int	get_each_ms(void);


#endif