#include "../includes/philo.h"

int main(int ac, char **av)
{
	if (ac < 5)
		return (1);
	if (check_args(av + 1))
		return (1);
	philo_init(av);
	return (0);
}
