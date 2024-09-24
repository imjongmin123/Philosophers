/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:26:53 by jonim             #+#    #+#             */
/*   Updated: 2023/07/13 14:35:48 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ph_list	*find_start_node(t_ph_list *ph_node)
{
	t_ph_list	*last_node;

	last_node = ph_node;
	while (1)
	{
		if (ph_node->number == 1)
		{
			last_node->next = ph_node;
			ph_node->pre = last_node;
			break ;
		}
		ph_node = ph_node->pre;
	}
	return (ph_node);
}

int	ph_data_init(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->num_of_philo = ph_atoi(argv[1]);
	data->time_die = 1000 * ph_atoi(argv[2]);
	data->time_eat = 1000 * ph_atoi(argv[3]);
	data->time_sleep = 1000 * ph_atoi(argv[4]);
	data->num_eat = 0;
	pthread_mutex_init(&(data->end_flag_key), NULL);
	pthread_mutex_init(&(data->print_key), NULL);
	gettimeofday(&(data->init_time), NULL);
	if (argc == 6)
		data->num_eat = ph_atoi(argv[5]);
	if (data->num_of_philo <= 0 || data->time_die <= 0 || data->time_eat <= 0 \
		|| data->time_sleep <= 0 || data->num_eat < 0)
		return (1);
	data->end_flag = 0;
	return (0);
}

void	ph_list_init(t_ph_list *ph_list, t_data *data, int num)
{
	ph_list->number = num;
	ph_list->data = data;
	ph_list->l_fork = 1;
	ph_list->r_fork = 1;
	ph_list->num_of_eat = 0;
	ph_list->pre = NULL;
	ph_list->next = NULL;
	pthread_mutex_init(&(ph_list->fork), NULL);
	pthread_mutex_init(&(ph_list->eat_num_key), NULL);
	pthread_mutex_init(&(ph_list->eat_time_key), NULL);
}

t_ph_list	*ph_init_philo(t_data *data)
{
	int			i;
	t_ph_list	*ph_list;

	ph_list = (t_ph_list *)malloc(sizeof(t_ph_list));
	if (!ph_list)
		return (NULL);
	ph_list_init(ph_list, data, 1);
	i = 1;
	while (i < data->num_of_philo)
	{
		ph_list->next = (t_ph_list *)malloc(sizeof(t_ph_list));
		if (!(ph_list->next))
			return (NULL);
		ph_list_init(ph_list->next, data, i + 1);
		ph_list->next->pre = ph_list;
		ph_list = ph_list->next;
		ph_list->next = NULL;
		i++;
	}
	return (find_start_node(ph_list));
}
