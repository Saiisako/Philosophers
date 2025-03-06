/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:18:02 by skock             #+#    #+#             */
/*   Updated: 2025/03/06 12:36:06 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(100);
	if (philo->table->nb_philosophers == 1)
	{
		print(philo, "is thinking");
		print(philo, "has taken a fork");
		usleep(philo->time_to_die * 1000);
		print(philo, "died");
		return (NULL);
	}
	while (1)
	{
		print(philo, "is thinking");
		if (verif_is_dead(philo))
			break;
		if (take_fork(philo) == 0)
			break ;
		if (eat_routine(philo) == 0)
			break ;
		if (verif_is_dead(philo))
			break;
	}
	return (NULL);
}

void	death_routine(t_table *table)
{
	int	i;
	int	j;
	
	
	if (table->nb_philosophers == 1)
		return ;
	while (1)
	{
		i = 0;
		j = 0;
		while (i < table->nb_philosophers)
		{
			if (dying(&table->philo[i]) == 0)
				return ;
			pthread_mutex_lock(&table->nb_meal_mutex);
			if (table->philo[i].nb_meal == 0 && table->meal == true)
			{
				j++;
				if (j == table->nb_philosophers)
				{
					pthread_mutex_lock(&table->dying_mutex);
					table->is_dead = true;
					pthread_mutex_unlock(&table->dying_mutex);
					pthread_mutex_unlock(&table->nb_meal_mutex);
					return ;
				}
			}
			pthread_mutex_unlock(&table->nb_meal_mutex);
			i++;
		}
	}
	return ;
}

int	main(int ac, char **av)
{
	t_table		*table;
	int			i;

	if (!verif_arg(ac, av))
		return (1);
	table = malloc(sizeof(t_table));
	table->nb_philosophers = ft_atoi(av[1]);
	table->philo = malloc(sizeof(t_philo) * table->nb_philosophers);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philosophers);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->nb_meal_mutex, NULL);
	pthread_mutex_init(&table->dying_mutex, NULL);
	pthread_mutex_init(&table->philo->last_meal_mutex, NULL);
	table->time_start = get_each_ms();
	table->meal = false;
	table->is_dead = false;
	i = 0;
	while (i < table->nb_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			free(table->philo);
			free(table);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < table->nb_philosophers)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork_mutex = &table->forks[i];
		table->philo[i].right_fork_mutex = &table->forks[(i + 1) % table->nb_philosophers];
		table->philo[i].time_to_die = ft_atoi(av[2]);
		table->philo[i].time_to_eat = ft_atoi(av[3]);
		table->philo[i].time_to_sleep = ft_atoi(av[4]);
		table->philo[i].table = table;
		table->philo[i].last_meal = get_each_ms();
		table->philo[i].is_eating = false;
		if (ac == 6)
		{
			table->philo[i].nb_meal = ft_atoi(av[5]);
			table->meal = true;
		}
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]) != 0)
			return (printf("Error: Failed to create thread\n"), 1);
		i++;
	}
	i = 0;
	death_routine(table);
	while (i < table->nb_philosophers)
		pthread_join(table->philo[i++].thread, NULL);
	free(table->philo);
	free(table);
	return (0);
}
