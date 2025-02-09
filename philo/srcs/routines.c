
#include "../headers/philo.h"

//TODO: philos should start together
//fix: races

int	monitor_check_ith_philo(t_info *info, unsigned int i);

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

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)arg;
	i = 0;
	if (philo->id % 2)
		usleep(ODD_PHILO_SLEEP_TIME);
	while (1)
	{
		i++;
		if (philo_eat(philo))
			return (NULL);
		if (philo->meal_count == i)
		{
			pthread_mutex_lock((philo->meal_count_mutex));
			++*(philo->meal_count_total);
			pthread_mutex_unlock((philo->meal_count_mutex));
		}
		if (philo_sleep(philo))
			return (NULL);
		if (philo->nb_philos % 2)
			if (philo_think(philo))
				return (NULL);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_info			*info;
	unsigned int	i;

	info = (t_info *)arg;
	while (1)
	{
		i = 0;
		while (i < info->nb)
		{
			if (monitor_check_ith_philo(info, i))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&(info->meal_count_mutex));
		if (info->meal_count_total == info->nb)
		{
			pthread_mutex_unlock(&(info->meal_count_mutex));
			pthread_mutex_lock(&(info->death_mutex));
			info->someone_died = 1;
			pthread_mutex_unlock(&(info->death_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(info->meal_count_mutex));
	}
	return (NULL);
}

int	monitor_check_ith_philo(t_info *info, unsigned int i)
{
	pthread_mutex_lock(&(info->philos[i].time_mutex));
	if (get_time() - info->philos[i].last_meal > info->tt_die)
	{
		pthread_mutex_unlock(&(info->philos[i].time_mutex));
		pthread_mutex_lock(&(info->death_mutex));
		info->someone_died = 1;
		pthread_mutex_unlock(&(info->death_mutex));
		pthread_mutex_lock(&(info->print_mutex));
		ft_printf_action(DIE, &(info->philos[i]));
		pthread_mutex_unlock(&(info->print_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(info->philos[i].time_mutex));
	// pthread_mutex_lock(&(info->philos[i].meal_count_mutex));
	// if (!meals[i] && info->philos[i].meal_count_reached)
	// {
	// 	pthread_mutex_unlock(&(info->philos[i].meal_count_mutex));
	// 	meals[i] = 'm';
	// 	if (ft_strlen(meals) == info->nb)
	// 	{
	// 		pthread_mutex_lock(&(info->death_mutex));
	// 		info->someone_died = 1;
	// 		pthread_mutex_unlock(&(info->death_mutex));
	// 		return (1);
	// 	}
	// 	pthread_mutex_lock(&(info->philos[i].meal_count_mutex)); // if possible, don't lock unnsesarily
	// }
	// pthread_mutex_unlock(&(info->philos[i].meal_count_mutex));
	return (0);
}
