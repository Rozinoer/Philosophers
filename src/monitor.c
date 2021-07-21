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

void	*monitoring(void *philo_v)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *)philo_v;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&philo->mutex);
		time = get_time();
		if (time - philo->last_meal > philo->main->time_to_die)
		{
			action(philo, DEAD);
			pthread_mutex_unlock(&philo->main->dead);
			pthread_mutex_lock(&philo->main->str);
			pthread_mutex_unlock(&philo->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}
