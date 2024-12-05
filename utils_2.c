/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:04:47 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/05 17:43:17 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/* fonction pour recuperer le temps actuel en millisecondes */
int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// conversion en millisecondes des secondes et des microsecondes
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

/* fonction dont le but est de realiser une pause pendant une duree
specifique, exprimee en millisecondes */
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	// initialisation de start avec l'heure actuelle
	start = get_time();
	// boucle pour surveiller la duree ecoulee
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

/* fonction qui va destroy toutes les mutex */
void	destroy_mutex(char *str, t_simulation *simulation, pthread_mutex_t *forks)
{
	int	i;

	if (str && *str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&simulation->print_lock);
	pthread_mutex_destroy(&simulation->meal_lock);
	pthread_mutex_destroy(&simulation->dead_lock);
	i = 0;
	while (i < simulation->philos[0].nb_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}