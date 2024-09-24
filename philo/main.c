/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:34:53 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 17:38:28 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_ph_list	*ph_list;

	if (ph_data_init(&data, argc, argv))
		return (1);
	ph_list = ph_init_philo(&data);
	while (1)
	{
		gettimeofday(&(ph_list->eat_time), NULL);
		pthread_create(&(ph_list->philo), NULL, philo_exe, ph_list);
		if (ph_list->next->number == 1)
			break ;
		ph_list = ph_list->next;
	}
	ph_list = ph_list->next;
	ph_cctv(ph_list);
	ph_thread_join(ph_list, ph_list->data->num_of_philo);
	ph_free(ph_list);
	return (0);
}
