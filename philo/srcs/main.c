/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:59 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/09 15:44:46 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	create_threads(t_info *in, pthread_t *thread_ids);

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
	if (init_locks(&info))
		destroy_infos(&info);
	start_simulation(&info);
	destroy_infos(&info);
	return (0);
}

//thread_ids is null-terminated array of pthread_t
void	start_simulation(t_info *in)
{
	pthread_t		*thread_ids;
	unsigned int	i;

	thread_ids = malloc(sizeof(pthread_t) * (in->nb + 1));
	if (!thread_ids)
		return ;
	ft_bzero(thread_ids, sizeof(pthread_t) * (in->nb + 1));
	if (in->nb == 1)
	{
		if (!pthread_create(&thread_ids[0], NULL, single_philo, &in->philos[0]))
			pthread_join(thread_ids[0], NULL);
		free(thread_ids);
		return ;
	}
	create_threads(in, thread_ids);
	i = 0;
	while (i <= in->nb && thread_ids[i])
		pthread_join(thread_ids[i++], NULL);
	free(thread_ids);
}

void	create_threads(t_info *in, pthread_t *thread_ids)
{
	unsigned int	i;

	i = 0;
	while (i < in->nb)
	{
		if (pthread_create(&thread_ids[i], NULL, philo_routine, &in->philos[i]))
		{
			thread_ids[i] = 0;
			break ;
		}
		i++;
	}
	if (thread_ids[i - 1] && \
		pthread_create(&thread_ids[i], NULL, monitor_routine, in))
		thread_ids[i] = 0;
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

void	ft_printinfo(t_info *info)
{
	printf("program running with:\n");
	printf("number of philosophers:	%d\n", info->nb);
	printf("time to die:			%d\n", info->tt_die);
	printf("time to eat:			%d\n", info->tt_eat);
	printf("time to sleep:			%d\n", info->tt_sleep);
	if (info->min_eat != 0)
		printf("times each philosopher must eat:	%d\n", info->min_eat);
	else
		printf("running indefinitely or till a philosopher dies\n");
}
