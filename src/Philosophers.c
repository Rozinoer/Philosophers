/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:01:49 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 17:01:53 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*eating(void *philo_v)
{
	t_philo		*philo;
	pthread_t	dead;

	philo = (t_philo *)philo_v;
	philo->last_meal = get_time();
	pthread_create(&dead, NULL, monitoring, philo_v);
	pthread_detach(dead);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
	}
	return (NULL);
}

static int mutex_destroy(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->amount)
	{
		pthread_mutex_destroy(&main->philos[i]->mutex);
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&main->dead);
	pthread_mutex_destroy(&main->common_eat);
	pthread_mutex_destroy(&main->str);
	free_p(main);
	free_argv(main->philos, main->amount);
	return (1);
}

int	main(int argc, char **argv)
{
	t_main		main;
	int			i;
	void		*philo;

	i = 0;
	if (argc < 5 || argc > 6)
		return (str_err("Error argument\n", 1));
	if (init(argc, argv, &main))
		return (str_err("Error init\n", 1));
	while (i < main.amount)
	{
		philo = (void *)(main.philos[i]);
		if (pthread_create(&main.philo[i], NULL, eating, philo) != 0)
			return (mutex_destroy(&main));
		pthread_detach(main.philo[i++]);
		usleep(100);
	}
	pthread_mutex_lock(&main.dead);
	pthread_mutex_unlock(&main.dead);
	write(1, "Exit\n", 5);
	return (mutex_destroy(&main) && 0);
}
