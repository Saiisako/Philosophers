/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_orders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:51:34 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 15:57:34 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_table("is thinking", philo);
	usleep(5000);
}

void	sleeping(t_philo *philo)
{
	print_table("is sleeping", philo);
	usleep(philo->table->time_to_sleep * 1000);
}

void	go_eat(t_philo *philo)
{
	print_table("has taken a fork", philo);
	print_table("has taken a fork", philo);
	print_table("is eating", philo);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	usleep(philo->table->time_to_eat * 1000);
}

void	eat(t_philo *philo, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		pthread_mutex_lock(philo->right_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		pthread_mutex_lock(philo->left_fork_mutex);
	}
	if (someone_dead(philo) == false)
		go_eat(philo);
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
	pthread_mutex_lock(&philo->meal_take_mutex);
	philo->meal_take += 1;
	pthread_mutex_unlock(&philo->meal_take_mutex);
}
