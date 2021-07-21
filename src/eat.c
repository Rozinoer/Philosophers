/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:00:37 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 17:00:39 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long int	get_time(void)
{
	long int time;
	static struct timeval	tv;

	time = 0;
	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * (long int)1000) + (tv.tv_usec / 1000));
	return (time);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->forks[philo->rfork]);
	action(philo, TAKE_FORKS);
	pthread_mutex_lock(&philo->main->forks[philo->lfork]);
	action(philo, TAKE_FORKS);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	if (philo->main->number_of_times >= 0)
	{
		pthread_mutex_lock(&philo->main->all_eat);
		if (philo->main->common_eat > 0 && philo->must_eat > 0)
		{
			action(philo, EAT);
			philo->main->common_eat--;
			philo->must_eat--;
		}
		else
			pthread_mutex_unlock(&philo->main->dead);
		pthread_mutex_unlock(&philo->main->all_eat);
	}
	else
		action(philo, EAT);
	ph_sleep(philo->main->time_to_eat);
	pthread_mutex_unlock(&philo->mutex);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->main->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->main->forks[philo->rfork]);
	action(philo, SLEEP);
	ph_sleep(philo->main->time_to_sleep);
	action(philo, THINK);
}
