/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:23:32 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/09 15:23:39 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

//take forks
//lock print_mutex
//print action
//unlock print_mutex
//set mealtime (maybe put this first?)
//release forks
int	philo_eat(t_philo *philo)
{
	if (philo_take_forks(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(EAT, philo);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->tt_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (EXIT_SUCCESS);
}

int	philo_take_forks(t_philo *philo)
{
	if (philo_needs_stop(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	if (philo_needs_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (EXIT_FAILURE);
	}
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(FORK, philo);
	ft_printf_action(FORK, philo);
	pthread_mutex_unlock(philo->print_mutex);
	if (philo_needs_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//maybe use philo->tt_eat as an approximation for get_time - last_meal
int	philo_sleep(t_philo *philo)
{
	if (philo_needs_stop(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(SLEEP, philo);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	if ((get_time() - philo->last_meal) + philo->tt_sleep > philo->tt_die)
	{
		pthread_mutex_unlock(&philo->time_mutex);
		usleep(philo->tt_die * 1000);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->tt_sleep * 1000);
	return (EXIT_SUCCESS);
}

int	philo_think(t_philo *philo)
{
	if (philo_needs_stop(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock(philo->print_mutex);
	ft_printf_action(THINK, philo);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(100);
	return (EXIT_SUCCESS);
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
