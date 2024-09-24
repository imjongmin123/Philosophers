/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:44:38 by jonim             #+#    #+#             */
/*   Updated: 2023/07/13 14:27:31 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_check_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] <= '9' && s[i] >= '0')
			i++;
		else
			return (1);
	}
	return (0);
}

long long	ph_atoi(char *str)
{
	int			i;
	int			rs;
	long long	sign;

	if (ph_check_str(str))
		return (-1);
	i = 0;
	rs = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rs = (rs * 10) + (str[i] - 48);
		i++;
	}
	return (sign * rs);
}
