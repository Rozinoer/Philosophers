#include "Philosophers.h"

int	free_argv(t_philo **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(argv[i]);
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