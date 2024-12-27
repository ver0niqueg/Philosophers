/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:25:01 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/27 19:34:15 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->nb_of_philos = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->nb_of_times_to_eat = ft_atol(argv[5]);
	else
		philo->nb_of_times_to_eat = -1;
}

/* fonction pour initialiser un tableau de philosophes avec tous les
parametres necessaires */
void	init_philos(t_philo *philos, t_simulation *simulation,
	pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].is_eating = 0;
		philos[i].meals_count = 0;
		init_input(&philos[i], argv);
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].print_lock = &simulation->print_lock;
		philos[i].dead_lock = &simulation->dead_lock;
		philos[i].meal_lock = &simulation->meal_lock;
		philos[i].dead = &simulation->death_detected;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].nb_of_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

/* fonction qui utilise des mutex pour les fourchettes = les fourchettes
doivent etre partagees entre les philos de maniere synchro pour eviter
les conflits */
int	init_forks(pthread_mutex_t *forks, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (printf("Failed to initialize\n"), -1);
		i++;
	}
	return (0);
}

int	init_simulation(t_simulation *simulation, t_philo *philos)
{
	simulation->death_detected = 0;
	simulation->philos = philos;
	if (pthread_mutex_init(&simulation->print_lock, NULL) != 0
		|| pthread_mutex_init(&simulation->dead_lock, NULL) != 0
		|| pthread_mutex_init(&simulation->meal_lock, NULL) != 0)
		return (printf("Failed to initialize\n"), -1);
	return (0);
}
