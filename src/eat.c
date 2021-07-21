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

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->forks[philo->lfork]);
	action(philo, TAKE_FORKS);
	pthread_mutex_lock(&philo->main->forks[philo->rfork]);
	action(philo, TAKE_FORKS);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->main->number_of_times >= 0)
	{
		pthread_mutex_lock(&philo->main->all_eat);
		if (philo->main->common_eat > 0 && philo->must_eat > 0)
		{
			philo->last_meal = get_time();
			action(philo, EAT);
			philo->main->common_eat--;
			philo->must_eat--;
		}
		else
			pthread_mutex_unlock(&philo->main->dead);
		pthread_mutex_unlock(&philo->main->all_eat);
	}
	else 
	{
		philo->last_meal = get_time();
		action(philo, EAT);
	}
	usleep(philo->main->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->main->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->main->forks[philo->rfork]);
	action(philo, SLEEP);
	usleep(philo->main->time_to_sleep * 1000);
	action(philo, THINK);
}
