/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:18:02 by skock             #+#    #+#             */
/*   Updated: 2025/03/07 15:08:18 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_philo_mutex(t_table **table, char **av)
{
	int	i;

	*table = malloc(sizeof(t_table));
	(*table)->nb_philosoph = ft_atoi(av[1]);
	(*table)->philo = malloc(sizeof(t_philo) * (*table)->nb_philosoph);
	(*table)->forks = malloc(sizeof(pthread_mutex_t) * (*table)->nb_philosoph);
	pthread_mutex_init(&(*table)->print_mutex, NULL);
	pthread_mutex_init(&(*table)->nb_meal_mutex, NULL);
	pthread_mutex_init(&(*table)->dying_mutex, NULL);
	pthread_mutex_init(&(*table)->philo->last_meal_mutex, NULL);
	(*table)->time_start = get_each_ms();
	(*table)->meal = false;
	(*table)->is_dead = false;
	i = 0;
	while (i < (*table)->nb_philosoph)
	{
		if (pthread_mutex_init(&(*table)->forks[i], NULL))
		{
			free((*table)->philo);
			free(table);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philosophers(t_table *table, char **av, int ac)
{
	int	i;

	i = 0;
	while (i < table->nb_philosoph)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork_mutex = &table->forks[i];
		table->philo[i].right_fork_mutex = &table->forks[(i + 1)
			% table->nb_philosoph];
		table->philo[i].time_to_die = ft_atoi(av[2]);
		table->philo[i].time_to_eat = ft_atoi(av[3]);
		table->philo[i].time_to_sleep = ft_atoi(av[4]);
		table->philo[i].table = table;
		table->philo[i].last_meal = get_each_ms();
		if (ac == 6)
		{
			table->philo[i].nb_meal = ft_atoi(av[5]);
			table->meal = true;
		}
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine,
				&table->philo[i]) != 0)
			return (printf("Error: Failed to create thread\n"), 1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table		*table;
	int			i;

	i = 0;
	if (!verif_arg(ac, av))
		return (1);
	if (malloc_philo_mutex(&table, av) == 1)
		return (1);
	if (init_philosophers(table, av, ac) == 1)
		return (1);
	death_routine(table);
	while (i < table->nb_philosoph)
		pthread_join(table->philo[i++].thread, NULL);
	free(table->philo);
	free(table);
	return (0);
}
