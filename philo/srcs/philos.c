
#include "../headers/philo.h"

void	philo_take_forks(t_philo	*philo);
void	philo_release_forks(t_philo	*philo)

int	philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_release_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ;
}

void	philo_take_forks(t_philo	*philo)
{
	if (philo->id % 2)
		usleep(ODD_PHILO_SLEEP_TIME);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
}

void	philo_release_forks(t_philo	*philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_eat(t_philo *philo)
{

}
