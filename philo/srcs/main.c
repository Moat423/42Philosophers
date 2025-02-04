/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/04 15:56:51 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	handle_input(int argc, char *argv[], t_info *info);

// argv[1] = number_of_philosophers
// argv[2] = time_to_die
// argv[3] = time_to_eat
// argv[4] = time_to_sleep
// argv[5] = [number_of_times_each_philosopher_must_eat]
int	main(int argc, char *argv[])
{
	t_info	info;

	if (handle_input(argc, argv, &info))
		return (1);
	return (0);
}

int	get_time(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000;
	return (time);
}

int	handle_input(int argc, char *argv[], t_info *info)
{
	if (argc < 4 || argc > 5)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	info->nb = ft_atoui(argv[1]);
	info->tt_die = ft_atoui(argv[2]);
	info->tt_eat = ft_atoui(argv[3]);
	info->tt_sleep = ft_atoui(argv[4]);
	if (argc == 6)
		info->must_eat = ft_atoui(argv[5]);
	else
		info->must_eat = -1;
	return (0);
}
