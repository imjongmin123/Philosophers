/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:26:00 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 18:02:29 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_usleep(long long time, t_ph_list *ph_list)
{
	long long	s;
	long long	n;

	time = time / 1000;
	s = ph_get_now_time(ph_list);
	while (1)
	{
		n = ph_get_now_time(ph_list);
		if (n - s >= time)
			break ;
		usleep(10);
	}
}

int	ph_get_fork(t_ph_list *ph_list)
{
	long long		s;

	pthread_mutex_lock(&(ph_list->data->print_key));
	if (ph_check_endflag(ph_list) == DEATH)
	{
		pthread_mutex_unlock(&(ph_list->data->print_key));
		return (1);
	}
	s = ph_get_now_time(ph_list);
	printf("%llu %d has taken a fork\n", s, ph_list->number);
	pthread_mutex_unlock(&(ph_list->data->print_key));
	return (0);
}

int	ph_eating(t_ph_list *ph_list)
{
	long long	millsec;

	pthread_mutex_lock(&(ph_list->data->print_key));
	if (ph_check_endflag(ph_list) == DEATH)
	{
		pthread_mutex_unlock(&(ph_list->data->print_key));
		return (1);
	}
	millsec = ph_get_eat_time(ph_list);
	printf("%llu %d is eating\n", millsec, ph_list->number);
	pthread_mutex_unlock(&(ph_list->data->print_key));
	pthread_mutex_lock(&(ph_list->eat_num_key));
	ph_list->num_of_eat++;
	pthread_mutex_unlock(&(ph_list->eat_num_key));
	ph_usleep(ph_list->data->time_eat, ph_list);
	return (0);
}

int	ph_sleeping(t_ph_list *ph_list)
{
	long long		s;

	pthread_mutex_lock(&(ph_list->data->print_key));
	{
		if (ph_check_endflag(ph_list) == DEATH)
		{
			pthread_mutex_unlock(&(ph_list->data->print_key));
			return (DEATH);
		}
		s = ph_get_now_time(ph_list);
		printf("%llu %d is sleeping\n", s, ph_list->number);
		pthread_mutex_unlock(&(ph_list->data->print_key));
		ph_usleep(ph_list->data->time_sleep, ph_list);
	}
	pthread_mutex_lock(&(ph_list->data->print_key));
	if (ph_check_endflag(ph_list) == DEATH)
	{
		pthread_mutex_unlock(&(ph_list->data->print_key));
		return (DEATH);
	}
	s = ph_get_now_time(ph_list);
	printf("%llu %d is thinking\n", s, ph_list->number);
	pthread_mutex_unlock(&(ph_list->data->print_key));
	return (SUCCESS);
}
