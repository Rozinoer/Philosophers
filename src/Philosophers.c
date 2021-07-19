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

// int	start(t_main *main)
// {
// 	pthread_t	thr;

// 	if (main->number_of_times > 0)
// 	{
// 		if (pthread_create(&thr, NULL, &monitoring_all, (void *)main) != 0)
// 			return (1);
// 		pthread_detach(thr);
// 	}
// 	return (0);
// }

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
			return (1);
		pthread_detach(main.philo[i++]);
		usleep(100);
	}
	// start(&main);
	pthread_mutex_lock(&main.died);
	pthread_mutex_unlock(&main.died);
	write(1, "Exit\n", 5);
	return (0);
}
