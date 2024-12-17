/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:29:49 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/17 17:33:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// faire une dead_loop pour check si un philo is dead

/* fonction pour checker en boucle si un philo est dead */
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	// si le philo est mort
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

/* fonction routine de thread avec les actions qu'un philo execute lors
de la simulation */
void	*philo_routine(void *arg) // ou data ?
{
	t_philo *philo;

	// conversion en type t_philo *
	philo = (t_philo *)arg;
	// les philo aux id pairs attendent avant de commencer
	// avec ce depart decale, on evite les deadlock au debut
	if (philo->id % 2 == 0)
		ft_usleep(1);
	// faire boucle de routine // tant qu'un philo n'est pas mort = 0/false
	while (!dead_loop(philo))
	{
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
	}
	return (arg);
}

// pas besoin de rajouter un ft_usleep ?

/* fonction pour creer les threads observer + philo */
// faire fonction destroy_all

int	create_philo_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	// creation d'un un thread par philo
	while (i < simulation->philos[0].nb_of_philos)
	{
		// associer chaque philo a un thread
		if (pthread_create(&simulation->philos[i].thread, NULL, &philo_routine,
				&simulation->philos[i]) != 0) // retourne 0 si ca marche
			{
				destroy_mutex("Fail to create thread", simulation, forks);
				return (1);
			}
		i++;
	}
	return (0);
}

int	join_philo_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < simulation->philos[0].nb_of_philos)
	{
		// la fonction dans la condition creer quand meme le thread
		if (pthread_join(simulation->philos[i].thread, NULL) != 0)
			destroy_mutex("Fail to join thread", simulation, forks);
		i++;
	}
	return (0);
}
// creer un thread supplementaire pour surveiller l'etat general de la simulation
int	start_simulation(t_simulation *simulation, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;

	// coder une fonction monitor
	if (pthread_create(&monitor_thread, NULL, &philo_monitoring, simulation->philos) != 0)
		destroy_mutex("Fail to create thread", simulation, forks);
	create_philo_threads(simulation, forks);
	// attendre que le thread de surveillance se termine
	if (pthread_join(monitor_thread, NULL) != 0)
		destroy_mutex("Fail to join thread", simulation, forks);
	join_philo_threads(simulation, forks);
	return (0);
}

// dans le fichier monitor faire des check pour avoir si ya un mort, si tous ont mange etc...