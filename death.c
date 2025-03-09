/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:49:31 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 15:58:51 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_thread(t_philo *philo)
{
	long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->last_eat_mutex);
	if ((current_time - philo->last_eat) >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_eat_mutex);
		pthread_mutex_lock(&philo->table->is_dead_mutex);
		if (philo->table->is_dead == 0)
		{
			philo->table->is_dead = 1;
			print_table("died", philo);
		}
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (true);
}

void	*monitoring(void *arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)arg;
	while (1)
	{
		while (i < table->nb_philosoph)
		{
			pthread_mutex_lock(&table->meal_max_mutex);
			pthread_mutex_lock(&table->philo[i].meal_take_mutex);
			if (check_thread(&table->philo[i]) == false || (table->meal_max != 0
					&& table->philo[i].meal_take == table->meal_max))
			{
				pthread_mutex_unlock(&table->philo[i].meal_take_mutex);
				pthread_mutex_unlock(&table->meal_max_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philo[i].meal_take_mutex);
			pthread_mutex_unlock(&table->meal_max_mutex);
			i++;
		}
		i = 0;
	}
	return (NULL);
}

bool	someone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->is_dead_mutex);
	if (philo->table->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->is_dead_mutex);
	return (false);
}
