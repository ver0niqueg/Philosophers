#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

#endif

typedef struct	s_philo
{
	pthread_t			thread;
	int					nb_of_philos;
	int					id;
	int					is_eating;
	int					meals_count;
	int					nb_of_times_to_eat; // meal goal
	int					*dead;
	size_t				time_to_die; // the time a philo will die if he doesnt eat
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

typedef struct	s_simulation
{
	int					dead_flag; // flag pour indiquer si un philo est mort
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	t_philo				*philos;
}						t_simulation;

/**** CHECKS *****/
int			is_digit(char *argv);
int			check_args(int argc, char **argv);

/**** INITIALIZATION *****/
void		init_input(t_philo *philo, char **argv);
void		init_philos(t_philo *philos, t_simulation *simulation,
			pthread_mutex_t *forks, char **argv);
void		init_forks(pthread_mutex_t *forks, int philo_nb);
void		init_simulation(t_simulation *simulation, t_philo *philos);

/**** ACTIONS *****/
void		print_logs(char *str, t_philo *philo, int id);
void		philo_is_thinking(t_philo *philos);
void		philo_is_sleeping(t_philo *philos);
void		philo_is_eating(t_philo *philo);
int			philo_is_dead(t_philo *philo, size_t time_to_die);

/**** UTILS ****/
static int	ft_isspace(int c);
size_t		ft_strlen(const char *str);
long		ft_atol(const char *str);
int			get_time(void);
int			ft_usleep(size_t milliseconds);

