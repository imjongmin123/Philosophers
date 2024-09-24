/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonim <jonim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:34:20 by jonim             #+#    #+#             */
/*   Updated: 2023/07/16 17:36:08 by jonim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define DEATH 1
# define SUCCESS 0
# define FAILURE 2

typedef struct s_data
{
	int				num_of_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				end_flag;
	pthread_mutex_t	end_flag_key;
	pthread_mutex_t	print_key;
	struct timeval	init_time;
}	t_data;

typedef struct s_ph_list
{
	int						number;
	int						num_of_eat;
	int						l_fork;
	int						r_fork;
	struct timeval			eat_time;
	pthread_t				philo;
	pthread_mutex_t			eat_num_key;
	pthread_mutex_t			fork;
	pthread_mutex_t			eat_time_key;
	struct s_data			*data;
	struct s_ph_list		*pre;
	struct s_ph_list		*next;
}	t_ph_list;

t_ph_list		*ph_init_philo(t_data *data);
t_ph_list		*find_start_node(t_ph_list *ph_node);
int				ph_data_init(t_data *data, int argc, char **argv);
void			ph_list_init(t_ph_list *ph_list, t_data *data, int num);
int				ph_sleeping(t_ph_list *ph_list);
int				ph_eating(t_ph_list *ph_list);
void			ph_usleep(long long time, t_ph_list *ph_list);
int				ph_get_fork(t_ph_list *ph_list);
int				ph_check_endflag(t_ph_list *ph_list);
void			ph_unlock(t_ph_list *ph_list, t_ph_list *ph_list2);
void			*philo_exe(void *arg);
int				ph_even_exe(t_ph_list *ph_list);
int				ph_odd_exe(t_ph_list *ph_list);
void			*ph_cctv(void *arg);
void			ph_end(t_ph_list *ph_list);
void			ph_die(t_ph_list *ph_list, int num);
int				ph_check_eat_time(t_ph_list *ph_list);
int				ph_check_eat_sum(t_ph_list *ph_list);
void			ph_free(t_ph_list *ph_list);
long long		ph_get_eat_time(t_ph_list *ph_list);
void			ph_thread_join(t_ph_list *ph_node, int num);
void			ph_free(t_ph_list *ph_list);
long long		ph_get_now_time(t_ph_list *ph_list);
long long		ph_atoi(char *str);
int				ph_even_exe(t_ph_list *ph_list);
int				ph_even_try_one(t_ph_list *ph_list, t_ph_list *ph_list2);
int				ph_even_try_two(t_ph_list *ph_list, t_ph_list *ph_list2);
int				ph_odd_exe(t_ph_list *ph_list);
int				ph_odd_try_two(t_ph_list *ph_list, t_ph_list *ph_list2);
int				ph_odd_try_one(t_ph_list *ph_list, t_ph_list *ph_list2);
int				ph_solo_exe(t_ph_list *ph_list);

#endif