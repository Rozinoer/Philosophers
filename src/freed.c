#include "Philosophers.h"

int	free_argv(t_philo **argv, int i)
{
	while (i-1 >= 0)
	{
		free(argv[i - 1]);
		i--;
	}
	free(argv);
	return (1);
}

int	free_p(t_main *main)
{
	free(main->forks);
    free(main->philo);
	return (1);
}