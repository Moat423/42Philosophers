#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

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
# define MAG "\033[35m"    // Magenta
# define CYN "\033[36m"    // Cyan
# define WHT "\033[37m"    // White
# define BRED "\033[1;31m" // Bold Red
# define RESET "\033[0m"
# define BOLD "\033[1m"

enum e_input_meaning
{
	number_of_philosophers						= 1,
	time_to_die									= 2,
	time_to_eat									= 3,
	time_to_sleep								= 4,
	number_of_times_each_philosopher_must_eat	= 5,
};

// Philosopher's ID
// Pointer to the right fork's mutex
// Pointer to the left fork's mutex
// Timestamp of the last meal
// Mutex to protect access to last_meal
// Number of meals the philosopher has eaten
// Flag indicating if the philosopher is dead
// Mutex to protect printing to the console
// Mutex to protect access to the death flag
// Pointer to a shared death flag
// Timestamp of the start time
// Time to die (in milliseconds)
// Time to eat (in milliseconds)
// Time to sleep (in milliseconds)
typedef struct s_philo
{
	unsigned int	id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	size_t			last_meal;
	pthread_mutex_t	time_mutex;
	unsigned int	meal_count;
	unsigned int	meal_count_reached;
	pthread_mutex_t	meal_count_mutex;
	int				dead;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	int				*death;
	size_t			start_time;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
}					t_philo;

typedef struct s_info
{
	unsigned int	nb;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	min_eat;
	t_philo			*philos;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}					t_info;
#endif //STRUCTS_H
