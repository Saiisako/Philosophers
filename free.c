/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:00:18 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 16:13:16 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo, t_table *table)
{
	if (table)
	{
		pthread_mutex_destroy(&table->is_dead_mutex);
		pthread_mutex_destroy(&table->start_time_mutex);
		pthread_mutex_destroy(&table->meal_max_mutex);
		pthread_mutex_destroy(&philo->last_eat_mutex);
		free(table->forks);
		free(table);
		table = NULL;
	}
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
}

void	destroy_mutex(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nb_philosoph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->nb_philosoph)
	{
		pthread_mutex_lock(&table->forks[i]);
		pthread_mutex_unlock(&table->forks[i]);
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_take_mutex);
		i++;
	}
}
