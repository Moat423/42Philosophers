/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/05 14:39:00 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int		handle_input(int argc, char *argv[], t_info *info);
int		get_time(void);
void	ft_printinfo(t_info *info);

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
	ft_printinfo(&info);
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

// TODO: handle min_eat == 0
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
		info->min_eat = ft_atoui(argv[5], &err);
	else
		info->min_eat = -1;
	if (err)
	{
		printf("usage:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat\n");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

void	ft_printinfo(t_info *info)
{
	printf("program running with:\n");
	printf("number of philosophers:	%d\n", info->nb);
	printf("time to die:			%d\n", info->tt_die);
	printf("time to eat:			%d\n", info->tt_eat);
	printf("time to sleep:			%d\n", info->tt_sleep);
	if (info->min_eat != -1)
		printf("number of times each philosopher must eat:	%d", info->min_eat);
	else
		printf("running indefinitely or till a philosopher dies");
}
