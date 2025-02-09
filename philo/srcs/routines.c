
#include "../headers/philo.h"

//TODO: philos should start together
//fix: races

int	monitor_check_ith_philo(t_info *info, unsigned int i, char *meals);

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
	if (philo->id % 2)
		usleep(ODD_PHILO_SLEEP_TIME);
	while (1)
	{
		i++;
		if (philo_eat(philo))
			return (NULL);
		if (philo->meal_count == i)
		{
			pthread_mutex_lock(&(philo->meal_count_mutex));
			philo->meal_count_reached = 1;
			pthread_mutex_unlock(&(philo->meal_count_mutex));
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
	char			*meal_count_reached;

	info = (t_info *)arg;
	meal_count_reached = malloc(sizeof(char) * info->nb);
	ft_bzero(meal_count_reached, sizeof(char) * info->nb);
	while (1)
	{
		i = 0;
		while (i < info->nb)
		{
			if (monitor_check_ith_philo(info, i, meal_count_reached))
			{
				free(meal_count_reached);
				return (NULL);
			}
			i++;
		}
	}
	free(meal_count_reached);
	return (NULL);
}

int	monitor_check_ith_philo(t_info *info, unsigned int i, char *meals)
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
	pthread_mutex_lock(&(info->philos[i].meal_count_mutex));
	if (!meals[i] && info->philos[i].meal_count_reached)
	{
		pthread_mutex_unlock(&(info->philos[i].meal_count_mutex));
		meals[i] = 'm';
		if (ft_strlen(meals) == info->nb)
		{
			pthread_mutex_lock(&(info->death_mutex));
			info->someone_died = 1;
			pthread_mutex_unlock(&(info->death_mutex));
			return (1);
		}
		pthread_mutex_lock(&(info->philos[i].meal_count_mutex)); // if possible, don't lock unnsesarily
	}
	pthread_mutex_unlock(&(info->philos[i].meal_count_mutex));
	return (0);
}
