
#include "../headers/philo.h"

int	destroy_philos(t_info *info);

int	init_locks(t_info *info)
{
	info->philos = NULL;
	info->forks = NULL;
	if (pthread_mutex_init(&(info->print_mutex), NULL))
	{
		pthread_mutex_destroy(&(info->print_mutex));
		free(info);
		info = NULL;
		return (1);
	}
	if (pthread_mutex_init(&(info->death_mutex), NULL))
	{
		pthread_mutex_destroy(&(info->print_mutex));
		pthread_mutex_destroy(&(info->death_mutex));
		free(info);
		info = NULL;
		return (1);
	}
	if (init_arrays(info))
	{
		destroy_infos(info);
		free(info);
		info = NULL;
		return (1);
	}
	return (0);
}

int	init_arrays(t_info *info)
{
	unsigned int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb);
	info->philos = malloc(sizeof(t_philo) * info->nb);
	if (!info->forks || !info->philos)
		return (destroy_infos(info));
	i = 0;
	while (i < info->nb)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (destroy_infos(info));
		ft_bzero((void *)&(info->philos[i]), sizeof(t_philo));
		if (pthread_mutex_init(&(info->philos[i].time_mutex), NULL))
			return (destroy_infos(info));
		if (pthread_mutex_init(&(info->philos[i].meal_count_mutex), NULL))
			return (destroy_infos(info));
		info->philos[i].id = i + 1;
		info->philos[i].meal_count = (info)->min_eat;
		info->philos[i].meal_count_reached = 0;
		info->philos[i].dead = 0;
		info->philos[i].print_mutex = &(info->print_mutex);
		info->philos[i].death_mutex = &(info->death_mutex);
		info->philos[i].death = &(info->someone_died);
		if (i % 2)
		{
			info->philos[i].right_fork = &(info->forks[i]);
			info->philos[i].left_fork = &(info->forks[(i + 1) % info->nb]);
		}
		else
		{
			info->philos[i].right_fork = &(info->forks[(i + 1) % info->nb]);
			info->philos[i].left_fork = &(info->forks[i]);
		}
		info->philos[i].start_time = get_time();
		info->philos[i].last_meal = info->philos->start_time;
		info->philos[i].tt_die = info->tt_die;
		info->philos[i].tt_eat = info->tt_eat;
		info->philos[i].tt_sleep = info->tt_sleep;
		info->philos[i].nb_philos = info->nb;
		i++;
	}
	return (0);
}

int	destroy_infos(t_info *info)
{
	unsigned int	i;

	pthread_mutex_destroy(&(info->print_mutex));
	pthread_mutex_destroy(&(info->death_mutex));
	i = 0;
	if (info->forks)
	{
		while (i < info->nb)
			pthread_mutex_destroy(&(info->forks[i++]));
	}
	free(info->forks);
	destroy_philos(info);
	return (1);
}

int	destroy_philos(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->nb)
	{
		pthread_mutex_destroy(&(info->philos[i].time_mutex));
		pthread_mutex_destroy(&(info->philos[i].meal_count_mutex));
		i++;
	}
	free(info->philos);
	return (1);
}

int	check_error(int err)
{
	if (err)
	{
		printf("usage:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat\n");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

int	handle_input(int argc, char *argv[], t_info *info)
{
	int	err;

	ft_bzero(info, sizeof(t_info));
	err = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	info->nb = ft_atoui(argv[1], &err);
	info->tt_die = ft_atoui(argv[2], &err);
	info->tt_eat = ft_atoui(argv[3], &err);
	info->tt_sleep = ft_atoui(argv[4], &err);
	if (argc == 6)
	{
		info->min_eat = ft_atoui(argv[5], &err);
		if (info->min_eat == 0 && err == 0)
		{
			printf("done\n");
			return (1);
		}
	}
	else
		info->min_eat = 0;
	return (check_error(err));
}
