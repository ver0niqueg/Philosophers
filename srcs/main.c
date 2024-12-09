/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:18:34 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/09 18:41:34 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5)
		return (0);
	if (ft_atol(argv[1]) <= 0 || is_digit(argv[1]) == 0)
		return (printf("Invalid number of philosophers\n"));
	if (ft_atol(argv[2]) <= 0 || is_digit(argv[2]) == 0)
		return (printf("Invalid time to die\n"));
	if (ft_atol(argv[3]) <= 0 || is_digit(argv[3]) == 0)
		return (printf("Invalid time to eat\n"));
	if (ft_atol(argv[4]) <= 0 || is_digit(argv[4]) == 0)
		return (printf("Invalid time to sleep\n"));
	if (argv[5] && (ft_atol(argv[5]) < 0 || is_digit(argv[5]) == 0))
		return (printf("Invalid number of times each philo must eat\n"));
	return (1);
}

int main(int argc, char **argv)
{
	t_simulation	simulation;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments\n"), 1);
	if (check_args(argc, argv) == 1)
		return (1);
	init_simulation(&simulation, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &simulation, forks, argv);
	start_simulation(&simulation, forks);
	destroy_mutex("End of simulation\n", &simulation, forks);
}
