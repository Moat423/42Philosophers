#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>

//init_destroy.c
int		handle_input(int argc, char *argv[], t_info *info);
int	init_locks(t_info *info);
int	init_arrays(t_info *info);
int	destroy_infos(t_info *info);
//utils.c
int		get_time(void);
void	ft_printinfo(t_info *info);
unsigned int	ft_atoui(const char *str, int *err);

#endif //PHILO_H
