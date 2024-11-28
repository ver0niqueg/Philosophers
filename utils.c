/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:28:19 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/28 20:38:00 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// faire fonction pour recuperer le temps actuel
// faire fonction pour faire une pause comme usleep
// faire une fonction pour destroy les mutex !!

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

long	ft_atol(const char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

/* fonction pour afficher un message dans un environnement ou il y a plusieurs
threads -> le but est d'afficher des messages simultanement en utilisant un
mutex pour synchroniser l'acces a l'operation d'ecriture */

void	print_action(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_time();
	// finir
}

/* fonction pour recuperer le temps actuel en millisecondes */
int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// conversion en millisecondes des secondes et des microsecondes
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
}