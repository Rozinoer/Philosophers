/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 16:57:43 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 16:57:47 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				pos;
	int				lfork;
	int				rfork;
	long int		last_meal;
	long int		limit;
	int				must_eat;
	struct s_main	*main;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_main
{
	int				amount;
	int				flag;
	int				common_eat;
	pthread_t		*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	str;
	pthread_mutex_t	all_eat;
	t_philo			**philos;
	long int		start;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				number_of_times;
}	t_main;

enum e_action
{
	TAKE_FORKS,
	PUT_FORKS,
	EAT,
	OVER,
	DEAD,
	SLEEP,
	THINK
};
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);
void		ph_sleep(int t);

void		*monitoring_all(void *main_v);
void		*monitoring(void *philo_v);
int			str_err(char *str, int code);
int			action(t_philo *philo, int type);

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			init(int argc, char **argv, t_main *main);
long int	get_time(void);

#endif
