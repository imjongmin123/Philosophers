/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:30:14 by jonim             #+#    #+#             */
/*   Updated: 2023/07/13 13:40:50 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_free(t_ph_list *ph_list)
{
	t_ph_list	*tmp;
	int			num;

	num = ph_list->data->num_of_philo;
	while (ph_list)
	{
		if (ph_list->number < num)
			tmp = ph_list->next;
		else
			tmp = NULL;
		pthread_mutex_destroy(&(ph_list->fork));
		pthread_mutex_destroy(&(ph_list->eat_num_key));
		pthread_mutex_destroy(&(ph_list->eat_time_key));
		free(ph_list);
		ph_list = tmp;
	}
}
