/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:23:25 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/27 15:51:03 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* fonction pour afficher un message -> le but est d'afficher des messages
simultanement en utilisant un mutex pour synchroniser l'acces a l'operation
d'ecriture affiche <temps ecoule> <id du philo> et <l'action> */
void	print_logs(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
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
	ft_usleep(philo->time_to_sleep);
}

void	philo_is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_logs("has taken a fork", philo, philo->id);
	if (philo->nb_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_logs("has taken a fork", philo, philo->id);
	philo->is_eating = 1;
	print_logs("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
