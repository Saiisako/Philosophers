/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:23:05 by skock             #+#    #+#             */
/*   Updated: 2025/02/26 16:57:19 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(void)
{
	
}

int get_each_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	eat_routine(t_philo *philo)
{
	if (philo->hold_fork == true)
	{
		philo->time_to_eat = get_each_ms();
		while (philo->is_eating == true)
		{
			philo->is_eating = true;
			if (philo->time_to_eat == 0)
				philo->is_eating = false;
		}
		return (1);
	}
	else
		return (0);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		pthread_mutex_lock(philo->right_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		pthread_mutex_lock(philo->left_fork_mutex);
		usleep(100);
	}
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

void	eat_routine(t_philo *philo)
{
	ft_usleep(philo->time_to_eat * 1000);
	drop_fork(philo);
	pthread_mutex_lock(&philo->table->last_meal_mutex);
	philo->last_meal = get_each_ms;
	pthread_mutex_unlock(&philo->table->last_meal_mutex);
	pthread_mutex_lock(&philo->table->nb_meal_mutex);
	if (philo->nb_meal)
		philo->nb_meal--;
	pthread_mutex_unlock(&philo->table->nb_meal_mutex);
	drop_fork(philo);
}

void	limited_routine(t_philo *philo)
{
	while (1)
	{
		take_fork(philo);
		eat_routine(philo);
		if (philo->nb_meal == 0)
		{
			printf("philosoph [%d] finishd eating", philo->id);
			break ;
		}
		if (philo->table->is_dead == 1)
		{
			printf("philosoph [%d] died", philo->id);
			break ;
		}
	}
	return ;
}
void	infinite_routine(t_philo *philo)
{
	while (1)
	{
		if (philo->table->is_dead == 1)
		{
			printf("philosoph [%d] died", philo->id);
			break ;
		}
	}
	return ;
}
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	if (philo->nb_meal)
		limited_routine(philo);
	else if (!philo->nb_meal)
		infinite_routine(philo);
	return (NULL);
}

void	death_routine(void *arg)
{
	t_philo	*table;
	int		i;
	
	table = (t_table *)arg;
	i = 0;
	while (1)
	{
		while ()
	}
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
	pthread_mutex_init(&table->is_dead_mutex, NULL);
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
		table->is_dead = false;
		table->philo[i].is_eating = false;
		if (ac == 6)
			table->philo[i].nb_meal = ft_atoi(av[5]);
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]) != 0)
			return (printf("Error: Failed to create thread\n"), 1);
		i++;
	}
	i = 0;
	if (pthread_create(&table->philo[i].thread, NULL, death_routine, &table->philo[i]) != 0)
			return (printf("Error: Failed to create thread\n"), 1);
	while (i + 1 < table->nb_philosophers)
		pthread_join(table->philo[i++].thread, NULL);
	free(table->philo);
	free(table);
	return (0);
}