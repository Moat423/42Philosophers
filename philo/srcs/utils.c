/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:25:44 by lmeubrin          #+#    #+#             */
/*   Updated: 2025/02/09 15:41:42 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	get_time(void);

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

void	ft_bzero(void *s, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < size)
		str[i++] = 0;
}

int	ft_printf_action(int action, t_philo *p)
{
	int		ret;
	size_t	time;

	ret = 0;
	time = get_time() - p->start_time;
	if (action == FORK)
		ret = printf(YEL"%zu %d has taken a fork\n"RESET, time, p->id);
	else if (action == EAT)
		ret = printf(MAG"%zu %d is eating\n"RESET, time, p->id);
	else if (action == SLEEP)
		ret = printf(BLUE"%zu %d is sleeping\n"RESET, time, p->id);
	else if (action == THINK)
		ret = printf(GREEN"%zu %d is thinking\n"RESET, time, p->id);
	else if (action == DIE)
		ret = printf(BRED"%zu %d died\n"RESET, time, p->id);
	return (ret);
}

int	get_time(void)
{
	struct timeval	tv;
	size_t			time;

	gettimeofday(&tv, NULL);
	time = (size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000;
	return (time);
}

//atoi to unsigned int with some errorchecking
//only returns result if success and sets err to EXIT_SUCCESS, else returns 0
//and sets err to 1
//suceeeds with a correctly null terminated string of solely digits 
//with an arbitraty ammount of whitespace in the beginning 
//followed by a single possible +
unsigned int	ft_atoui(const char *str, int *err)
{
	unsigned long	nb;
	size_t			i;

	nb = 0;
	if (!(*str))
		return (0);
	i = 0;
	while (((str[i] >= '\t') && (str[i] <= '\r')) || (str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		nb = nb * 10 + str[i++] - '0';
	if (!str[i] && nb <= (unsigned long) UINT_MAX)
	{
		*err = 0;
		return ((unsigned int) nb);
	}
	*err = 1;
	return (0);
}
