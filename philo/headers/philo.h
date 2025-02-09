#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>

//main.c
void			ft_printinfo(t_info *info);
void			start_simulation(t_info *info);
//init_destroy.c
int				handle_input(int argc, char *argv[], t_info *info);
int				init_locks(t_info *info);
int				init_arrays(t_info *info);
int				destroy_infos(t_info *info);
//utils.c
int				get_time(void);
void			ft_bzero(void *s, size_t size);
int				ft_printf_action(int action, t_philo *p);
unsigned int	ft_atoui(const char *str, int *err);
//routines.c
void			*philo_routine(void *arg);
void			*single_philo(void *arg);
void			*monitor_routine(void *arg);
//philos.c
int				philo_take_forks(t_philo *philo);
int				philo_die(t_philo *philo);
int				philo_sleep(t_philo *philo);
int				philo_think(t_philo *philo);
int				philo_needs_stop(t_philo *philo);
int				philo_eat(t_philo *philo);

#endif //PHILO_H
