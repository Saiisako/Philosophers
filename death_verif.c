/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:21:37 by skock             #+#    #+#             */
/*   Updated: 2025/03/06 12:36:21 by skock            ###   ########.fr       */
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
		{
			print(philo, "is eating");
			return (1);
		}
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
