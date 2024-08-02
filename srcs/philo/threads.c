/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:03:42 by shatan            #+#    #+#             */
/*   Updated: 2024/07/30 14:51:55 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_create(data->thread_arr + i, NULL, philo_run,
			data->philo_arr + i);
		i++;
	}
	data->vars.start_time = get_current_ms();
	i = 0;
	while (i < data->philo_count)
	{
		data->philo_arr[i].state = S_THINKING;
		data->philo_arr[i++].last_eat = data->vars.start_time;
	}
}

void	end_all_threads(t_data *data)
{
	int	i;

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