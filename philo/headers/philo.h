#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <sys/time.h>
# include <stdio.h>

unsigned int	ft_atoui(const char *str);

typedef struct s_info
{
	unsigned int	nb;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	int				must_eat;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				fork;
	int				last_meal;
	int				meal_count;
	volatile int	dead;
	volatile int	is_eating;
}					t_philo;
# endif //PHILO_H
