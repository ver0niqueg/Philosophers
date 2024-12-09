/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:23:25 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/09 19:23:42 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* fonction pour afficher un message dans un environnement ou il y a plusieurs
threads -> le but est d'afficher des messages simultanement en utilisant un
mutex pour synchroniser l'acces a l'operation d'ecriture */
void	print_logs(char *str, t_philo *philo, int id)
{
	size_t	time;
	// verrou pour qu'un seul thread a la fois ecrive
	pthread_mutex_lock(philo->print_lock);
	time = get_time() - philo->start_time;
	// check de l'etat du programme (si un philo est mort par ex)
	if (!philo_is_dead(philo)) // coder fonction philo_dead
		// affiche <temps ecoule> <id du philo> et <l'action>
		printf("%zu, %d, %s\n", time, id, str);
	// unlock le verrou
	pthread_mutex_unlock(philo->print_lock);
}

/* afficher un message pour l'action, faire attendre le philo et
gerer threads et synchronisation */
void	philo_is_thinking(t_philo *philo)
{
	print_logs("is thinking", philo, philo->id);
}

void	philo_is_sleeping(t_philo *philo)
{
	print_logs("is sleeping", philo, philo->id);
	// simulation du comportement is_sleeping avec une pause
	ft_usleep(philo->time_to_sleep);
}

void	philo_is_eating(t_philo *philo)
{
	// verrou pour les fourchettes
	pthread_mutex_lock(philo->left_fork);
	print_logs("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->right_fork);
	print_logs("has taken a fork", philo, philo->id);
	if (!philo->is_eating)
	{
		philo->is_eating = 1; // indique que le philo mange
		print_logs("is eating", philo, philo->id);
		// verrou pour le meal_lock
		pthread_mutex_lock(philo->meal_lock);
	}
	// recuperer le temps
	philo->last_meal = get_time();
	// incrementer le nb de repas manges
	philo->meals_count++;
	// deverouillage du meal_lock
	pthread_mutex_unlock(philo->meal_lock);
	// faire un pause le temps du repas
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	// repas termine on peut unlock les forks
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// gerer le cas lorsqu'il n'y a qu'un seul philo ??
