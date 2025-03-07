/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:39:19 by skock             #+#    #+#             */
/*   Updated: 2025/03/06 14:40:51 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		print(philo, "has taken a fork");
		if (verif_is_dead(philo))
			return (pthread_mutex_unlock(philo->left_fork_mutex), 0);
		pthread_mutex_lock(philo->right_fork_mutex);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		print(philo, "has taken a fork");
		if (verif_is_dead(philo))
			return (pthread_mutex_unlock(philo->right_fork_mutex), 0);
		pthread_mutex_lock(philo->left_fork_mutex);
		print(philo, "has taken a fork");
	}
	return (1);
}

void	drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
}
