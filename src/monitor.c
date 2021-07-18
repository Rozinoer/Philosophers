/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:01:42 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 17:01:43 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*monitoring_all(void *main_v)
{
	t_main	*main;
	int		must_eat;
	int		i;

	i = 0;
	must_eat = 0;
	main = (t_main *)main_v;
	while (must_eat < main->number_of_times)
	{
		i = 0;
		while (i < main->amount)
			pthread_mutex_lock(&main->philos[i++]->count);
		must_eat++;
	}
	action(main->philos[0], OVER);
	return (0);
}

void	*monitoring(void *philo_v)
{
	t_philo		*philo;
	uint64_t	time;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		time = get_time();
		if (!philo->eat && (time - philo->last_meal
				> philo->main->time_to_die))
		{
			action(philo, DEAD);
			pthread_mutex_unlock(&philo->main->died);
			pthread_mutex_unlock(&philo->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}
