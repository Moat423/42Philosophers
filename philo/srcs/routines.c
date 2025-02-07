
#include "../headers/philo.h"

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_printf_action(FORK, philo);
	usleep(philo->tt_die * 1000);
	philo->dead = 1;
	ft_printf_action(DIE, philo);
	return (NULL);
}

// maybe move calculating how many meals it has been to monitor thread to make this faster
void	*philo_routine(void *arg)
{
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)arg;
	i = 0;
	while (!philo->meal_count || i++ < philo->meal_count)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&(info->time));
		if (get_time() - info->philos->last_meal > info->tt_die)
		{
			pthread_mutex_lock(&(info->death_mutex));
			info->someone_died = 1;
			pthread_mutex_unlock(&(info->death_mutex));
			pthread_mutex_unlock(&(info->time));
			return (NULL);
		}
		pthread_mutex_unlock(&(info->time));
	}
}
