/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_gt_cf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:30:19 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 18:03:50 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_unlock(t_ph_list *ph_list, t_ph_list *ph_list2)
{
	pthread_mutex_unlock(&(ph_list->fork));
	pthread_mutex_unlock(&(ph_list2->fork));
	ph_list->l_fork = 1;
	ph_list->r_fork = 1;
}

long long	ph_get_eat_time(t_ph_list *ph_list)
{
	long long	s;

	s = 0;
	pthread_mutex_lock(&(ph_list->eat_time_key));
	gettimeofday(&(ph_list->eat_time), NULL);
	pthread_mutex_unlock(&(ph_list->eat_time_key));
	s = (ph_list->eat_time.tv_sec - ph_list->data->init_time.tv_sec) * \
	1000;
	s = s + (ph_list->eat_time.tv_usec - \
	ph_list->data->init_time.tv_usec) / 1000;
	return (s);
}

long long	ph_get_now_time(t_ph_list *ph_list)
{
	long long		ret;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec - ph_list->data->init_time.tv_sec) * 1000 \
	+ (time.tv_usec - ph_list->data->init_time.tv_usec) / 1000;
	return (ret);
}

int	ph_check_endflag(t_ph_list *ph_list)
{
	int	flag;

	flag = 1;
	while (1)
	{
		flag = pthread_mutex_lock(&(ph_list->data->end_flag_key));
		if (flag == 0)
		{
			if (ph_list->data->end_flag == 1)
			{
				pthread_mutex_unlock(&(ph_list->data->end_flag_key));
				return (DEATH);
			}
			else
			{
				pthread_mutex_unlock(&(ph_list->data->end_flag_key));
				return (FAILURE);
			}
		}
		else
			continue ;
		usleep(150);
	}
	return (SUCCESS);
}
