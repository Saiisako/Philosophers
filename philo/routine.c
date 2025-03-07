/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:36:39 by skock             #+#    #+#             */
/*   Updated: 2025/03/07 14:25:26 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_each_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->table->nb_meal_mutex);
	if (philo->nb_meal)
		philo->nb_meal--;
	pthread_mutex_unlock(&philo->table->nb_meal_mutex);
	print(philo, "is eating");
	if (ft_usleep(philo->time_to_eat * 1000, philo) == 0)
	{
		drop_fork(philo);
		return (0);
	}
	drop_fork(philo);
	print(philo, "is sleeping");
	if (ft_usleep(philo->time_to_sleep * 1000, philo) == 0)
		return (0);
	return (1);
}

void	solo_routine(t_philo *philo)
{
	print(philo, "is thinking");
	print(philo, "has taken a fork");
	usleep(philo->time_to_die * 1000);
	print(philo, "died");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(100);
	if (philo->table->nb_philosoph == 1)
	{
		solo_routine(philo);
		return (NULL);
	}
	while (1)
	{
		print(philo, "is thinking");
		if (verif_is_dead(philo))
			break ;
		if (take_fork(philo) == 0)
			break ;
		if (eat_routine(philo) == 0)
			break ;
		if (verif_is_dead(philo))
			break ;
	}
	return (NULL);
}
