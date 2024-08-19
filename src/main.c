#include "../includes/philosophers.h"

int main(int ac, char **av)
{
	if (ac < 5)
		return (1);
	philo_init();
	return (0);
}	