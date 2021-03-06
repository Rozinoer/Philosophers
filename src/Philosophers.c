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
	if (philo->pos % 2 == 0)
		ph_sleep(philo->main->time_to_eat);
	philo->last_meal = get_time();
	pthread_create(&dead, NULL, monitoring, philo_v);
	pthread_detach(dead);
	while (philo->main->flag)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
	}
	return (NULL);
}

int	freed(t_main *main, int ret)
{
	int	i;

	i = 0;
	while (i < main->amount)
	{
		if (pthread_mutex_destroy(&main->philos[i]->mutex) == 1
			|| pthread_mutex_destroy(&main->forks[i]) == 1)
			ret = 3;
		i++;
	}
	if (pthread_mutex_destroy(&main->dead) == 1
		|| pthread_mutex_destroy(&main->str) == 1
		|| pthread_mutex_destroy(&main->all_eat) == 1)
		ret = 3;
	i = main->amount - 1;
	while (i >= 0)
	{
		free(main->philos[i]);
		i--;
	}
	free(main->philos);
	free(main->forks);
	free(main->philo);
	return (ret);
}

int	start_thread(t_main *main)
{
	int		i;
	void	*philo;

	i = 0;
	while (i < main->amount)
	{
		philo = (void *)(main->philos[i]);
		if (pthread_create(&main->philo[i], NULL, eating, philo) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < main->amount)
	{
		pthread_join(main->philo[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main		main;

	if (argc < 5 || argc > 6)
		return (str_err("Error argument\n", 1));
	if (init(argc, argv, &main))
		return (str_err("Error init\n", 1));
	main.start = get_time();
	if (start_thread(&main) == 1)
		return (freed(&main, 1));
	return (freed(&main, 0));
}
