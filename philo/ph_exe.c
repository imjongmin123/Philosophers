/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:24:57 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 17:51:02 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_solo_exe(t_ph_list *ph_list)
{
	if (ph_get_fork(ph_list))
		return (DEATH);
	return (SUCCESS);
}

void	*philo_exe(void *arg)
{
	t_ph_list	*ph_list;

	ph_list = (t_ph_list *)arg;
	if (ph_list->data->num_of_philo == 1)
		ph_solo_exe(ph_list);
	else if (ph_list->number % 2 == 0)
		ph_even_exe(ph_list);
	else
		ph_odd_exe(ph_list);
	return (NULL);
}
