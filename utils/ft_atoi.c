/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:02:15 by dmyesha           #+#    #+#             */
/*   Updated: 2021/07/18 17:02:16 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_atoi(const char *str)
{
	int			minus_in_num;
	long long	number;

	minus_in_num = 0;
	number = 0;
	while ((*str >= 7 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		minus_in_num = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		number = number * 10 + (*str - 48);
		str++;
	}
	if ((number > (number * 10)) && minus_in_num)
		return (0);
	if (number > (number * 10))
		return (-1);
	if (minus_in_num)
		return ((int)number * -1);
	return ((int)number);
}
