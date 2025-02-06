#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>

# define ODD_PHILO_SLEEP_TIME 100  // microseconds

# define ERROR 2

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YEL "\033[33m"
# define BLUE "\033[34m"
# define RESET "\033[0m"
# define BOLD "\033[1m"

//init_destroy.c
int		handle_input(int argc, char *argv[], t_info *info);
int	init_locks(t_info *info);
int	init_arrays(t_info *info);
int	destroy_infos(t_info *info);
//utils.c
int		get_time(void);
void	ft_printinfo(t_info *info);
unsigned int	ft_atoui(const char *str, int *err);

enum e_input_meaning
{
	number_of_philosophers						= 1,
	time_to_die									= 2,
	time_to_eat									= 3,
	time_to_sleep								= 4,
	number_of_times_each_philosopher_must_eat	= 5,
};

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long long		last_meal;
	int				meal_count;
	int				dead;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*death_mutex;
}					t_philo;

typedef struct s_info
{
	unsigned int	nb;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	min_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}					t_info;

typedef struct s_data
{
	const int		total_philos;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t
}					t_data;

#endif //PHILO_H
