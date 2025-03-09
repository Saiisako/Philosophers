/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:49:13 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 16:08:00 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	limited_routine(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->table->meal_max_mutex);
		if (i == philo->table->meal_max)
		{
			pthread_mutex_unlock(&philo->table->meal_max_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->meal_max_mutex);
		if (someone_dead(philo))
			return ;
		think(philo);
		if (someone_dead(philo))
			return ;
		eat(philo, philo->id);
		if (someone_dead(philo))
			return ;
		sleeping(philo);
		if (someone_dead(philo))
			return ;
		i++;
	}
}

void	unlimited_routine(t_philo *philo)
{
	while (1)
	{
		if (someone_dead(philo))
			return ;
		think(philo);
		if (someone_dead(philo))
			return ;
		eat(philo, philo->id);
		if (someone_dead(philo))
			return ;
		sleeping(philo);
		if (someone_dead(philo))
			return ;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->meal_max_mutex);
	if (philo->table->meal_max == 0)
	{
		pthread_mutex_unlock(&philo->table->meal_max_mutex);
		unlimited_routine(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->meal_max_mutex);
		limited_routine(philo);
	}
	return (NULL);
}
