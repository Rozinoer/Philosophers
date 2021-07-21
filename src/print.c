/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:01:58 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 17:02:00 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	str_err(char *str, int code)
{
	printf("%s", str);
	return (code);
}

void	stop_sim(long int time, int pos, int type)
{
	if (type == OVER)
		printf ("\033[0;31mOVER\033[0m\n");
	else if (type == DEAD)
		printf ("\033[0;31m%ld %d is DEAD!\033[0m\n", time, pos);
}

void	sim(long int time, int pos, int type)
{
	if (type == TAKE_FORKS)
		printf ("%ld %d has token a fork!\n", time, pos);
	else if (type == SLEEP)
		printf ("%ld %d is sleeping!\n", time, pos);
	else if (type == THINK)
		printf ("%ld %d is thinking!\n", time, pos);
	else if (type == EAT)
		printf ("%ld %d is eating!\n", time, pos);
}

int	action(t_philo *philo, int type)
{
	static int	done;
	long int	time;

	done = 1;
	pthread_mutex_lock(&philo->main->str);
	time = get_time() - philo->main->start;
	if (done)
	{
		sim(time, philo->pos, type);
		if (type == DEAD || type == OVER)
		{
			done = 0;
			stop_sim(time, philo->pos, type);
			pthread_mutex_unlock(&philo->main->dead);
			pthread_mutex_lock(&philo->main->str);
		}
	}
	pthread_mutex_unlock(&philo->main->str);
	return (0);
}
