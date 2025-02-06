/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/06 19:29:42 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// argv[1] = number_of_philosophers
// argv[2] = time_to_die
// argv[3] = time_to_eat
// argv[4] = time_to_sleep
// argv[5] = [number_of_times_each_philosopher_must_eat]
int	main(int argc, char *argv[])
{
	t_info	info;
	t_data	data;

	if (handle_input(argc, argv, &info))
		return (1);
	ft_printinfo(&info);
	if (!init_locks(info))
		destroy_infos(info);
	if (!start_simulation(info))
		destroy_infos(info);
	return (0);
}

void	ft_printinfo(t_info *info)
{
	printf("program running with:\n");
	printf("number of philosophers:	%d\n", info->nb);
	printf("time to die:			%d\n", info->tt_die);
	printf("time to eat:			%d\n", info->tt_eat);
	printf("time to sleep:			%d\n", info->tt_sleep);
	if (info->min_eat != 0)
		printf("number of times each philosopher must eat:	%d", info->min_eat);
	else
		printf("running indefinitely or till a philosopher dies");
}
