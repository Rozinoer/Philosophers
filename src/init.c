/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:01:35 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 17:01:36 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	init_mutex(t_main *main, int i)
{
	while (i > 0)
	{
		pthread_mutex_init(&main->forks[i - 1], NULL);
		i--;
	}
	main->start = get_time();
	pthread_mutex_init(&main->dead, NULL);
	pthread_mutex_init(&main->str, NULL);
	pthread_mutex_init(&main->common_eat, NULL);
	pthread_mutex_lock(&main->dead);
}

static int	init_each_philo(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->amount)
	{
		main->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		main->philos[i]->main = main;
		main->philos[i]->eat = main->number_of_times;
		main->philos[i]->pos = i + 1;
		main->philos[i]->lfork = i;
		if (i + 1 == main->amount)
			main->philos[i]->rfork = 0;
		else
			main->philos[i]->rfork = i + 1;
		pthread_mutex_init(&main->philos[i]->mutex, NULL);
		i++;
	}
	return (0);
}

int	check_argv(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (str_err("Error: argument\n", 1));
	if (ft_atoi(argv[2]) <= 0)
		return (str_err("Error: argument\n", 1));
	if (ft_atoi(argv[3]) <= 0)
		return (str_err("Error: argument\n", 1));
	if (ft_atoi(argv[4]) <= 0)
		return (str_err("Error: argument\n", 1));
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0)
			return (str_err("Error: argument\n", 1));
	}
	return (0);
}

static int	set_param(t_main *main, char **argv, int argc)
{
	main->amount = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	main->number_of_times = -1;
	if (argc == 6)
	{
		main->number_of_times = ft_atoi(argv[5]);
		main->must_eat = main->number_of_times * main->amount;
	}
	main->philo = NULL;
	main->forks = NULL;
	main->philos = NULL;
	return (1);
}

int	init(int argc, char **argv, t_main *main)
{
	if (set_param(main, argv, argc) && check_argv(argc, argv))
		return (1);
	main->philo = (pthread_t *)malloc(sizeof(pthread_t) * (main->amount));
	if (!main->philo)
		return (str_err("Error: malloc\n", 1));
	main->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * (main->amount));
	if (!main->forks)
		return (str_err("Error: malloc\n", 1) && free_p(main));
	main->philos = (t_philo **)malloc(sizeof(t_philo *) * main->amount);
	if (!main->philos)
		return (str_err("Error: malloc\n", 1) && free_p(main));
	init_each_philo(main);
	init_mutex(main, main->amount);
	return (0);
}
