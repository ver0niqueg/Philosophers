/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:13 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/26 14:59:13 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t			thread;
	int					nb_of_philos;
	int					id;
	int					is_eating;
	int					meals_count;
	int					nb_of_times_to_eat;
	int					*dead;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				last_meal;
	size_t				start_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}						t_philo;

typedef struct s_simulation
{
	int					death_detected;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philos;
}						t_simulation;

/**** MAIN *****/
int			check_args(char **argv);

/**** INITIALIZATION *****/
void		init_input(t_philo *philo, char **argv);
void		init_philos(t_philo *philos, t_simulation *simulation,
				pthread_mutex_t *forks, char **argv);
int			init_forks(pthread_mutex_t *forks, int philo_nb);
int			init_simulation(t_simulation *simulation, t_philo *philos);

/**** ACTIONS *****/
void		print_logs(char *str, t_philo *philo, int id);
void		philo_is_thinking(t_philo *philos);
void		philo_is_sleeping(t_philo *philos);
void		philo_is_eating(t_philo *philo);

/*** PHILO ROUTINE ****/
int			dead_loop(t_philo *philo);
void		*philo_routine(void *arg);
int			create_philo_threads(t_simulation *simulation,
				pthread_mutex_t *forks);
int			join_philo_threads(t_simulation *simulation,
				pthread_mutex_t *forks);
int			start_simulation(t_simulation *simulation, pthread_mutex_t *forks);

/**** PHILO MONITORING ****/
int			philo_is_dead(t_philo *philo, size_t time_to_die);
int			dead_check(t_philo *philos);
int			all_philos_are_full(t_philo *philos);
void		*philo_monitoring(void *arg);

/**** UTILS ****/
int			is_digit(char *str);
size_t		ft_strlen(const char *str);
long		ft_atol(const char *str);
int			get_time(void);
int			ft_usleep(size_t milliseconds);
void		destroy_mutex(char *str, t_simulation *simulation,
				pthread_mutex_t *forks);

#endif