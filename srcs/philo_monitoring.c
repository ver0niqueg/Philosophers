/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:21:18 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/17 17:29:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// 2 cas d'arret de la simulation : un mort ou le nb de repas requis a ete atteint

// fichier monitoring "surveillance de la simulation"
// checker si un philo est mort, si tout le monde a mange, etc...

// fonction qui verifie si un philo donne est dead / appel dans la 2e
// fonction qui verifie si un philo est dead

/* fonction qui check si un philo est mort en fonction du
temps ecoule depuis son dernier repas. Si ce temps est >
au time_to_die et si le philo n'est pas en train de manger,
la fonction considere que le philo est dead */
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
int	dead_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_of_philos)
	{
		if (philo_is_dead(&philos[i], philos[i].time_to_die))
		{
			print_logs("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[i].dead_lock); // pourquoi rajouter philos[0]. ?
			*philos[i].dead = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

/* fonction aui check si tous les philos ont mange le nb min de repas requis
avant de considerer la simulation comme terminee */
int	all_philos_are_full(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	// si la simulation n'impose pas de nb minimal de repas indique par -1
	// on retourne 0 puisque la condition est inutile
	if (philos[0].nb_of_times_to_eat == -1)
		return (0);
	// boucle pour parcourir tous les philos et avoir si chacun a mange suffisamment
	while (i < philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		// si le philo courant a mange le nb de repas requis ou + on incremente
		if (philos[i].meals_count >= philos[i].nb_of_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	// cas si tout les philos ont termine leurs repas
	if (finished_eating == philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1; // tous les philos ont fini de manger
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

/* fonction qui surveille la simulation / la routine des philos */
void	*philo_monitoring(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
		if (dead_check(philos) == 1 || all_philos_are_full(philos) == 1)
			break;
	return (arg); // le pointeur initial est retourne
}