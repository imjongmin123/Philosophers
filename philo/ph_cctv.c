/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_cctv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:56:04 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 17:58:01 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_check_eat_sum(t_ph_list *ph_list)
{
	int	i;

	i = 0;
	while (i < ph_list->data->num_of_philo)
	{
		pthread_mutex_lock(&(ph_list->eat_num_key));
		if (ph_list->num_of_eat < ph_list->data->num_eat)
		{
			pthread_mutex_unlock(&(ph_list->eat_num_key));
			return (0);
		}
		pthread_mutex_unlock(&(ph_list->eat_num_key));
		ph_list = ph_list->next;
		i++;
	}
	return (1);
}

int	ph_check_eat_time(t_ph_list *ph_list)
{
	long long		millsec;
	struct timeval	cctv;

	pthread_mutex_lock(&(ph_list->eat_time_key));
	gettimeofday(&cctv, NULL);
	millsec = (cctv.tv_sec - ph_list->eat_time.tv_sec) * 1000 + \
	(cctv.tv_usec - ph_list->eat_time.tv_usec) / 1000;
	millsec = millsec * 1000;
	if (millsec >= ph_list->data->time_die)
	{
		pthread_mutex_unlock(&(ph_list->eat_time_key));
		return (1);
	}
	pthread_mutex_unlock(&(ph_list->eat_time_key));
	return (0);
}

void	ph_die(t_ph_list *ph_list, int num)
{
	long long	millsec;

	millsec = ph_get_now_time(ph_list);
	pthread_mutex_lock(&(ph_list->data->print_key));
	pthread_mutex_lock(&(ph_list->data->end_flag_key));
	ph_list->data->end_flag = 1;
	millsec = ph_get_now_time(ph_list);
	printf("%llu %d died\n", millsec, num);
	pthread_mutex_unlock(&(ph_list->data->print_key));
	pthread_mutex_unlock(&(ph_list->data->end_flag_key));
}

void	ph_end(t_ph_list *ph_list)
{
	pthread_mutex_lock(&(ph_list->data->end_flag_key));
	ph_list->data->end_flag = 1;
	pthread_mutex_unlock(&(ph_list->data->end_flag_key));
}

void	*ph_cctv(void *arg)
{
	t_ph_list	*ph_list;

	ph_list = (t_ph_list *)arg;
	while (1)
	{
		if (ph_check_eat_time(ph_list) > 0)
		{
			ph_die(ph_list, ph_list->number);
			return (NULL);
		}
		if (ph_list->data->num_eat > 0 && ph_check_eat_sum(ph_list))
		{
			ph_end(ph_list);
			return (NULL);
		}
		ph_list = ph_list->next;
		usleep(150);
	}
	return (NULL);
}
