
#include "../headers/philo.h"
#include "limits.h"

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
