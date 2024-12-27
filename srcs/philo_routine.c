/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:29:49 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/27 17:26:04 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* fonction pour checker en boucle si un philo est dead, est-ce que
death_detected a change de valeur ? */
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

/* fonction routine de thread avec les actions qu'un philo execute lors
de la simulation, depart decale pour les philos pairs */
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		philo_is_eating(philo);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
	}
	return (arg);
}

/* fonction pour creer les philo threads */
int	create_philo_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < simulation->philos[0].nb_of_philos)
	{
		if (pthread_create(&simulation->philos[i].thread, NULL, philo_routine,
				&simulation->philos[i]) != 0)
		{
			destroy_mutex("Fail to create thread", simulation, forks);
			return (1);
		}
		i++;
	}
	return (0);
}

/* fonction qui synchronise les threads, elle permet d'attendre la fin d'un
thread specifique, de recuperer son resultat et de liberer ses ressources */
int	join_philo_threads(t_simulation *simulation, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < simulation->philos[0].nb_of_philos)
	{
		if (pthread_join(simulation->philos[i].thread, NULL) != 0)
			destroy_mutex("Fail to join thread", simulation, forks);
		i++;
	}
	return (0);
}

/* creer un thread supplementaire pour surveiller l'etat general de la
 simulation */
int	start_simulation(t_simulation *simulation, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &philo_monitoring,
			simulation->philos) != 0)
		destroy_mutex("Fail to create thread", simulation, forks);
	create_philo_threads(simulation, forks);
	if (pthread_join(monitor_thread, NULL) != 0)
		destroy_mutex("Fail to join thread", simulation, forks);
	join_philo_threads(simulation, forks);
	return (0);
}
