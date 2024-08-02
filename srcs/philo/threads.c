/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:03:42 by shatan            #+#    #+#             */
/*   Updated: 2024/08/02 17:08:36 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_all_threads(t_data *data)
{
	int	i;

	i = 0;
	data->vars.start_time = get_current_ms();
	while (i < data->philo_count)
	{
		pthread_create(data->thread_arr + i, NULL, philo_run, data->philo_arr
			+ i);
		i++;
	}
}

void	end_all_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
		data->philo_arr[i++].state = S_DEAD;
	i = 0;
	while (i < data->philo_count)
	{
		pthread_detach(data->thread_arr[i]);
		pthread_mutex_destroy(data->fork_arr + i);
		++i;
	}
}
