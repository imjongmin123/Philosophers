/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:38:54 by jonim             #+#    #+#             */
/*   Updated: 2023/07/13 13:39:16 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_thread_join(t_ph_list *ph_node, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(ph_node->philo, NULL);
		ph_node = ph_node->next;
		i++;
		if (ph_node->number == 1)
			break ;
	}
}
