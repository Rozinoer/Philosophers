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
	philo->eat = 1;
	philo->last_meal = get_time();
	if (philo->main->number_of_times >= 0)
	{
		pthread_mutex_lock(&philo->main->common_eat);
		philo->main->must_eat--;
		pthread_mutex_unlock(&philo->main->common_eat);
	}
	action(philo, EAT);
	usleep(philo->main->time_to_eat * 1000);
	philo->eat = 0;
	pthread_mutex_unlock(&philo->mutex);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->main->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->main->forks[philo->rfork]);
	pthread_mutex_lock(&philo->main->common_eat);
	if (philo->main->number_of_times >= 0)
	{
		if(philo->main->must_eat == 0)
			action(philo, OVER);
	}
	pthread_mutex_unlock(&philo->main->common_eat);
	action(philo, SLEEP);
	usleep(philo->main->time_to_sleep * 1000);
	action(philo, THINK);
}
