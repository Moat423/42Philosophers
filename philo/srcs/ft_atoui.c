
//atoi to unsigned int
unsigned int	ft_atoui(const char *str)
{
	int		nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	if (!(*str))
		return (0);
	i = 0;
	while (((str[i] >= '\t') && (str[i] <= '\r')) || (str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		nb = nb * 10 + str[i++] - '0';
	nb *= sign;
	return (nb);
}
