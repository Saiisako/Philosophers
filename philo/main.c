/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:23:05 by skock             #+#    #+#             */
/*   Updated: 2025/02/18 15:37:26 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_each_second(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philosopher %d started\n", philo->id);
	printf("Philosopher %d finished sleeping\n", philo->id);
	return (NULL);
}

int	verif_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Invalid number of arguments!\n"), 0);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return (printf("Error: Number of philosophers must be between 1 and 200.\n"), 0);
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (printf("Error: Time values must be positive integers.\n"), 0);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (printf("Error: Eat count must be positive.\n"), 0);
	return (1);
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
	i = 0;
	table->nb_forks = ft_atoi(av[1]);
	printf("%d\n", table->nb_forks);
	while (i < table->nb_philosophers)
	{
		table->philo[i].id = i + 1;
		table->philo[i].time_to_die = ft_atoi(av[2]);
		table->philo[i].time_to_eat = ft_atoi(av[3]);
		table->philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			table->philo[i].nb_meal = ft_atoi(av[5]);
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]) != 0)
			return (printf("Error: Failed to create thread\n"), 1);
		i++;
	}
	i = 0;
	while (i < table->nb_philosophers)
		pthread_join(table->philo[i++].thread, NULL);
	free(table->philo);
	free(table);
	return (0);
}
