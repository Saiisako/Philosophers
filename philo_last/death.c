/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:33:14 by skock             #+#    #+#             */
/*   Updated: 2025/03/07 19:01:52 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->table->dying_mutex);
	if (get_each_ms() - philo->last_meal >= philo->time_to_die + 9)
	{
		philo->table->is_dead = true;
		pthread_mutex_unlock(&philo->table->dying_mutex);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dying_mutex);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->table->dying_mutex);
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->dying_mutex);
		if (philo->table->meal == true)
			return (1);
		print(philo, "died");
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dying_mutex);
	return (0);
}

int	dying(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (get_each_ms() - philo->last_meal >= philo->time_to_die + 9)
	{
		print(philo, "died");
		pthread_mutex_lock(&philo->table->dying_mutex);
		philo->table->is_dead = true;
		pthread_mutex_unlock(&philo->table->dying_mutex);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (1);
}

int	meal_check(t_table *table, int i, int *j)
{
	pthread_mutex_lock(&table->nb_meal_mutex);
	if (table->philo[i].nb_meal == 0 && table->meal == true)
	{
		(*j)++;
		if (*j == table->nb_philosoph)
		{
			pthread_mutex_lock(&table->dying_mutex);
			table->is_dead = true;
			pthread_mutex_unlock(&table->dying_mutex);
			pthread_mutex_unlock(&table->nb_meal_mutex);
			return (0);
		}
	}
	pthread_mutex_unlock(&table->nb_meal_mutex);
	return (1);
}

void	death_routine(t_table *table)
{
	int	i;
	int	j;

	if (table->nb_philosoph == 1)
		return ;
	while (1)
	{
		i = 0;
		j = 0;
		while (i < table->nb_philosoph)
		{
			if (dying(&table->philo[i]) == 0)
				return ;
			if (meal_check(table, i, &j) == 0)
				return ;
			i++;
		}
	}
	return ;
}
