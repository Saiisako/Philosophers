/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:18:02 by skock             #+#    #+#             */
/*   Updated: 2025/03/09 15:58:45 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table		*table;
	t_philo		*philo;
	pthread_t	monitoring;
	int			i;

	i = 0;
	table = NULL;
	philo = NULL;
	monitoring = 0;
	if (ac < 5 || ac > 6)
		return (printf("Error : wrong numbers of parameters\n"), 0);
	table = init_table(table, ac, av, philo);
	philo = malloc(sizeof(t_philo) * table->nb_philosoph);
	if (table->nb_philosoph == 1)
		one_philo(philo, table);
	else
		init_philo(philo, table, monitoring, i);
	return (0);
}
