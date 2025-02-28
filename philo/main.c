/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:23:05 by skock             #+#    #+#             */
/*   Updated: 2025/02/28 06:11:08 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->is_dead_mutex);
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->is_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->is_dead_mutex);
	return (0);
}

int get_each_ms(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("[%d] philo [%d] %s\n", get_each_ms() - philo->table->time_start, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

int	dying(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dying_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (get_each_ms() - philo->last_meal >= philo->time_to_die)
	{
		philo->table->is_dead = true;
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_unlock(&philo->table->dying_mutex);
		print(philo, "died");
		return (0);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->table->dying_mutex);
	return (1);
}

int	ft_usleep(int time, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		usleep(time / 10);
		i++;
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
		pthread_mutex_lock(philo->right_fork_mutex);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		print(philo, "has taken a fork");
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
		return (0);
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
	while (1)
	{
		// if (verif_is_dead(philo))
		// 	break;
		print(philo, "is thinking");
		if (take_fork(philo) == 0)
			break ;
		if (eat_routine(philo) == 0)
			break ;
		if (dying(philo) == 0)
			break ;
	}
	return (NULL);
}

void	death_routine(t_table *table)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < table->nb_philosophers)
		{
			pthread_mutex_lock(&table->is_dead_mutex);
			if (dying(&table->philo[i]) == 0)
			{
				table->is_dead = true;
				pthread_mutex_unlock(&table->is_dead_mutex);
				return ;
			}
			pthread_mutex_unlock(&table->is_dead_mutex);
			pthread_mutex_lock(&table->is_dead_mutex);
			if (table->philo[i].table->is_dead == true)
			{
				pthread_mutex_unlock(&table->is_dead_mutex);
				print(&table->philo[i], "died.");
				return ;
			}
			pthread_mutex_unlock(&table->is_dead_mutex);
			pthread_mutex_lock(&table->nb_meal_mutex);
			if (table->philo[i].nb_meal == 0 && table->meal == true)
			{
				j++;
				if (j == table->nb_philosophers)
				{
					pthread_mutex_lock(&table->is_dead_mutex);
					table->is_dead = true;
					pthread_mutex_unlock(&table->is_dead_mutex);
					pthread_mutex_unlock(&table->nb_meal_mutex);
					printf("everyone finished eating !\n");
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
	pthread_mutex_init(&table->is_dead_mutex, NULL);
	pthread_mutex_init(&table->nb_meal_mutex, NULL);
	pthread_mutex_init(&table->dying_mutex, NULL);
	pthread_mutex_init(&table->philo->last_meal_mutex, NULL);
	table->time_start = get_each_ms();
	table->meal = false;
	printf("%d\n", table->time_start);
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
