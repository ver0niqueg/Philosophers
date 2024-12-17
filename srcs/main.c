/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:18:34 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/17 18:20:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(int argc, char **argv)
{

	if (argc != 5)
		return (0);
	if (ft_atol(argv[1]) > PHILO_MAX || ft_atol(argv[1]) <= 0 || is_digit(argv[1]) == 1)
		return (printf("Invalid number of philosophers\n"), 1);
	if (ft_atol(argv[2]) <= 0 || is_digit(argv[2]) == 1)
		return (printf("Invalid time to die\n"), 1);
	if (ft_atol(argv[3]) <= 0 || is_digit(argv[3]) == 1)
		return (printf("Invalid time to eat\n"), 1);
	if (ft_atol(argv[4]) <= 0 || is_digit(argv[4]) == 1)
		return (printf("Invalid time to sleep\n"), 1);
	if (argv[5] && (ft_atol(argv[5]) < 0 || is_digit(argv[5]) == 1))
		return (printf("Invalid number of times each philo must eat\n"), 1);
	return (0);
}

int main(int argc, char **argv)
{
	t_simulation	simulation;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	printf("start program\n");
	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments\n"), 1);
	if (check_args(argc, argv) == 1)
		return (1);
	init_simulation(&simulation, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &simulation, forks, argv);
	start_simulation(&simulation, forks);
	destroy_mutex("End of simulation", &simulation, forks);
	return (0);
}
