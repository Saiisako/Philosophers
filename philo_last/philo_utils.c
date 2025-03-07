/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:31:43 by skock             #+#    #+#             */
/*   Updated: 2025/03/07 14:54:21 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	get_each_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_usleep(int time, t_philo *philo)
{
	int	i;

	i = -1;
	if (verif_is_dead(philo))
		return (0);
	while (++i < 10)
	{
		usleep(time / 10);
		if (verif_is_dead(philo))
			return (0);
	}
	return (1);
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->dying_mutex);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->is_dead == false)
		printf("%d %d %s\n", get_each_ms() - philo->table->time_start,
			philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
	pthread_mutex_unlock(&philo->table->dying_mutex);
}
