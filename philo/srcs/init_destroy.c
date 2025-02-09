/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:23:53 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/09 15:49:47 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	destroy_philos(t_info *info);

int	init_locks(t_info *info)
{
	info->philos = NULL;
	info->forks = NULL;
	if (pthread_mutex_init(&(info->print_mutex), NULL))
	{
		free(info);
		info = NULL;
		return (1);
	}
	if (pthread_mutex_init(&(info->death_mutex), NULL))
	{
		pthread_mutex_destroy(&(info->print_mutex));
		free(info);
		info = NULL;
		return (1);
	}
	if (pthread_mutex_init(&(info->meal_count_mutex), NULL))
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
		if (pthread_mutex_init(&(info->philos[i].time_mutex), NULL))
			return (destroy_infos(info));
		info->philos[i].id = i + 1;
		info->philos[i].meal_count = (info)->min_eat;
		info->philos[i].tt_die = info->tt_die;
		info->philos[i].tt_eat = info->tt_eat;
		info->philos[i].tt_sleep = info->tt_sleep;
		info->philos[i].nb_philos = info->nb;
		info->philos[i].meal_count_total = &(info->meal_count_total);
		info->philos[i].print_mutex = &(info->print_mutex);
		info->philos[i].death_mutex = &(info->death_mutex);
		info->philos[i].meal_count_mutex = &(info->meal_count_mutex);
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
		i++;
	}
	return (0);
}

int	destroy_infos(t_info *info)
{
	unsigned int	i;

	pthread_mutex_destroy(&(info->print_mutex));
	pthread_mutex_destroy(&(info->death_mutex));
	pthread_mutex_destroy(&(info->meal_count_mutex));
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
		i++;
	}
	free(info->philos);
	return (1);
}
