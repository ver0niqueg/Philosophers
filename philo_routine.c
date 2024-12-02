/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:29:49 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/02 20:19:45 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// faire une dead_loop pour check si un philo is dead

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
	// faire boucle de routine

}