/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:34:21 by skock             #+#    #+#             */
/*   Updated: 2025/02/19 14:25:10 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
