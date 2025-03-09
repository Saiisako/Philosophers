/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:01 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 16:10:13 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*solo_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	printf("%ld %d is thinking\n", get_time() - table->start_time,
		table->philo->id);
	printf("%ld %d has taken a fork\n", get_time() - table->start_time,
		table->philo->id);
	usleep(table->time_to_die * 1000);
	printf("%ld %d died\n", get_time() - table->start_time, table->philo->id);
	return (NULL);
}

void	one_philo(t_philo *philo, t_table *table)
{
	table->start_time = get_time();
	table->philo = philo;
	philo->id = 1;
	philo->last_eat = table->start_time;
	philo->left_fork_mutex = &table->forks[0];
	philo->right_fork_mutex = &table->forks[(0 + 1) % table->nb_philosoph];
	philo->meal_take = 0;
	if (pthread_create(&philo->thread, NULL, solo_routine, table) != 0)
		return ;
	pthread_join(philo->thread, NULL);
	free_all(philo, table);
}
