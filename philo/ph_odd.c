/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_odd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:33:49 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 18:03:14 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_odd_try_two(t_ph_list *ph_list, t_ph_list *ph_list2)
{
	while (1)
	{
		if (ph_check_endflag(ph_list) == DEATH)
			return (DEATH);
		if (ph_list->r_fork == 1)
		{
			ph_list->r_fork = pthread_mutex_lock(&(ph_list2->fork));
			if (ph_get_fork(ph_list) == DEATH)
				return (DEATH);
			if (ph_eating(ph_list) == DEATH)
				return (DEATH);
			ph_unlock(ph_list, ph_list2);
			if (ph_sleeping(ph_list) == DEATH)
				return (DEATH);
		}
		else
			usleep(30);
	}
	return (SUCCESS);
}

int	ph_odd_try_one(t_ph_list *ph_list, t_ph_list *ph_list2)
{
	if (ph_list->l_fork == 1)
	{
		ph_list->l_fork = pthread_mutex_lock(&(ph_list->fork));
		if (ph_get_fork(ph_list))
		{
			ph_list->l_fork = 1;
			pthread_mutex_unlock(&(ph_list->fork));
			return (DEATH);
		}
		if (ph_odd_try_two(ph_list, ph_list2) == DEATH)
		{
			ph_unlock(ph_list, ph_list2);
			return (DEATH);
		}
	}
	return (FAILURE);
}

int	ph_odd_exe(t_ph_list *ph_list)
{
	while (1)
	{
		if (ph_check_endflag(ph_list) == DEATH)
			return (DEATH);
		if (ph_odd_try_one(ph_list, ph_list->next) == FAILURE)
			usleep(30);
		else if (ph_odd_try_one(ph_list, ph_list->next) == DEATH)
			return (DEATH);
	}
	return (0);
}
