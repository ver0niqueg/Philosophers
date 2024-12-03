/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:29:49 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/03 17:16:48 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// faire une dead_loop pour check si un philo is dead

/* fonction pour checker en boucle si un philo est dead */
int	dead_loop(t_philo *philo)
{
	pthrad_mutex_lock(philo->dead_lock);
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
void	philo_routine(void *args) // ou data ?
{
	t_philo *philo;

	// conversion en type t_philo *
	philo = (t_philo *)args;
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
	return (0);
}
// pas besoin de rajouter un ft_usleep ?