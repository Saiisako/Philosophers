/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:34:21 by skock             #+#    #+#             */
/*   Updated: 2025/03/06 17:48:36 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	verif_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Invalid number of arguments!\n"), 0);
	if (av[5])
		if (!is_digit(av[5]))
			return (printf("Error: Values must be postive integers.\n"), 0);
	if (!is_digit(av[1]) || !is_digit(av[2]) || !is_digit(av[3])
		|| !is_digit(av[4]))
		return (printf("Error: Values must be postive integers.\n"), 0);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200.\n");
		return (0);
	}
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (printf("Error: Time values must be positive integers.\n"), 0);
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (printf("Error: Eat count must be positive.\n"), 0);
	return (1);
}
