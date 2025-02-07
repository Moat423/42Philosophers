
#include "../headers/philo.h"
#include <pthread.h>

//take forks
//lock print_mutex
//print action
//unlock print_mutex
//release forks
//set mealtime (maybe put this first?)
void	philo_eat(t_philo *philo)
{
	philo_take_forks(philo);
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(EAT, philo);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->tt_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2)
		usleep(ODD_PHILO_SLEEP_TIME);
	if (philo_needs_stop(philo))
		return ;
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(FORK, philo);
	pthread_mutex_unlock(philo->print_mutex);
	if (philo_needs_stop(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(FORK, philo);
	pthread_mutex_unlock(philo->print_mutex);
}

void	philo_sleep(t_philo *philo)
{
	if (philo_needs_stop(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(SLEEP, philo);
	pthread_mutex_unlock(philo->print_mutex);
	if (philo->last_meal + philo->tt_sleep < philo->tt_die)
	{
		usleep(philo->tt_sleep * 1000);
		return ;
	}
	usleep(philo->tt_die * 1000);
	philo_die(philo);
	return ;
}

//TODO: remove this function for norminette
void	philo_die(t_philo *philo)
{
	if (philo_needs_stop(philo))
		return ;
	philo->dead = 1;
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(DIE, philo);
	pthread_mutex_unlock(philo->print_mutex);
}

void	philo_think(t_philo *philo)
{
	if (philo_needs_stop(philo))
		return ;
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(THINK, philo);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(100);
}

int	philo_needs_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*(philo->death))
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}
