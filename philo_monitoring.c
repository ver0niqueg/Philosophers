/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:21:18 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/06 20:49:29 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// 2 cas d'arret de la simulation : un mort ou le nb de repas requis a ete atteint

// fichier monitoring "surveillance de la simulation"
// checker si un philo est mort, si tout le monde a mange, etc...

// fonction qui verifie si un philo donne est dead / appel dans la 2e
// fonction qui verifie si un philo est dead

/* fonction qui check si un philo donne est dead */
int	philo_is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	// condition pour check si le temps ecoule depuis le last meal est > au
	// temps a un philo pour mourir
	if (get_time() - philo->last_meal >= time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1); // oui il est dead
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}
/* fonction qui check dans un tableau de philo si il y en a qui sont dead.
Elle verifie si un philo est mort et met a jour l'etat global en consequence */
int dead_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_of_philos)
	{
		if (philo_is_dead(&philos[i], philos[i].time_to_die))
		{
			print_logs("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock); // pourquoi rajouter philos[0]. ?
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}