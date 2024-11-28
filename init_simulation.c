/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:25:01 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/28 19:31:02 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/* fonction pour initialiser l'input = conversion des arguments char en int
grace a la fonction ft_atoi */
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
	int	i; // variable pour iterer sur chaque philo

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1; // les id commencent a 1
		philos[i].is_eating = 0;
		philos[i].meals_count = 0;
		init_input(&philos[i], argv);
		philos[i].last_meal =
		philos[i].start_time =
		// pour une synchronisation des messages
		philos[i].print_lock = &simulation->print_lock;
		// pour gerer l'etat de mort du philosophe
		philos[i].dead_lock = &simulation->dead_lock;
		// pour eviter que 2 philos mangent en meme temps
		philos[i].meal_lock = &simulation->meal_lock;
		// pour check de facon centralisee si la simulation doit se terminer
		philos[i].dead = &simulation->dead_flag;
		// chaque philo prend la fourchette a gauche
		philos[i].left_fork = &forks[i];
		// si le philo est le premier il prend la derniere fourchette
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].nb_of_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
	}
}

/* fonction qui utilise des mutex pour les fourchettes = les fourchettes
doivent etre partagees entre les philos de maniere synchro pour eviter
les conflits (un philo qui essaye d'utiliser une fourchette deja prise) */
void	init_forks(pthread_mutex_t *forks, int philo_nb)
{
	int i;

	i = 0;
	while (i < philo_nb)
	{
		pthreadt_mutex_init(&forks[i], NULL);
		i++;
	}
}

// function to initialize the structure
void	init_simulation(t_simulation *simulation, t_philo *philos)
{
	simulation->dead_flag = 0;
	simulation->philos = philos;
	pthread_mutex_init(&simulation->print_lock, NULL);
	pthread_mutex_init(&simulation->dead_lock, NULL);
	pthread_mutex_init(&simulation->meal_lock, NULL);

}

/*
***
****

pthread_mutex_init est une fonction de la bibliotheque POSIX
utilisee pour initialiser un mutex, qui est une primitive de
synchronisation. Un mutex est utilise pour proteger des sections
du code, en assurant qu'un seul thread a la fois peut acceder a
une ressource partagee (=fourchette)

Voici son prototype :
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

****
***
*/