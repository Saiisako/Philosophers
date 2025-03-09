/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:55 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 16:16:30 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_table **table, t_philo *philo, int i)
{
	(void)philo;
	while (i < (*table)->nb_philosoph)
	{
		if (pthread_mutex_init(&(*table)->forks[i], NULL) != 0)
		{
			free_all(philo, *table);
			return ;
		}
		i++;
	}
}

void	init_philo(t_philo *philo, t_table *table, pthread_t monitoring_t,
int i)
{
	table->start_time = get_time();
	table->philo = philo;
	while (i < table->nb_philosoph)
	{
		philo[i].table = table;
		philo[i].id = i + 1;
		philo[i].last_eat = table->start_time;
		philo[i].left_fork_mutex = &table->forks[i];
		philo[i].right_fork_mutex = &table->forks[(i + 1)
			% table->nb_philosoph];
		philo[i].meal_take = 0;
		pthread_mutex_init(&philo[i].last_eat_mutex, NULL);
		pthread_mutex_init(&philo[i].meal_take_mutex, NULL);
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return ;
		i++;
	}
	pthread_create(&monitoring_t, NULL, monitoring, table);
	pthread_join(monitoring_t, NULL);
	destroy_mutex(table, philo);
	free_all(philo, table);
}

t_table	*init_table(t_table *table, int ac, char **av, t_philo *philo)
{
	int	i;

	table = malloc(sizeof(t_table));
	table->nb_philosoph = ft_atoi(av[1]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philosoph);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->is_dead = 0;
	pthread_mutex_init(&table->is_dead_mutex, NULL);
	pthread_mutex_init(&table->start_time_mutex, NULL);
	pthread_mutex_init(&table->meal_max_mutex, NULL);
	if (ac == 6)
		table->meal_max = ft_atoi(av[5]);
	else
		table->meal_max = 0;
	i = 0;
	init_fork(&table, philo, i);
	return (table);
}
