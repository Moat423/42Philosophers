
#include "../headers/philo.h"

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
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb);
	info->philos = malloc(sizeof(t_philo) * info->nb);
	if (!info->forks || !info->philos)
		return (destroy_infos(info));
	i = -1;
	while (++i < info->nb)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (destroy_infos(info));
		info->philos[i].id = i + 1;
		info->philos[i].last_meal = get_time();
		info->philos[i].meal_count = 0;
		info->philos[i].dead = 0;
		info->philos[i].print_lock = &(info->print_mutex);
		info->philos[i].death_mutex = &(info->death_mutex);
		info->philos[i].right_fork = &(info->forks[i]);
		info->philos[i].left_fork = &(info->forks[(i + 1) % info->nb]);
	}
	return (0);
}

int	destroy_infos(t_info *info)
{
	int	i;

	pthread_mutex_destroy(&(info->print_mutex));
	pthread_mutex_destroy(&(info->death_mutex));
	i = -1;
	if (info->forks)
	{
		while (++i < info->nb)
			pthread_mutex_destroy(&(info->forks[i]));
	}
	free(info->forks);
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

