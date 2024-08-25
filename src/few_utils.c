#include "../includes/philo.h"

size_t	ft_length(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	str_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_length(s));
}
