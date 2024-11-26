#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

#endif

typedef struct	s_philo
{
	pthread_t			thread;
	int					nb_philos;
	int					id;
	int					is_eating; // si le philo est en train de manger
	int					meals_eaten; // le nb de repas que le philo a mange -> progression du philo
	int					nb_times_to_eat; // objectif a atteindre (cb il doit manger)
	int					*dead;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				last_meal; // le temps du dernier repas du philo
	size_t				start_time; // le temps auquel le philo commence son activite
	pthread_mutex_t		right_fork;
	pthread_mutex_t		left_fork;
}				t_philo;
