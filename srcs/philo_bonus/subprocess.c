/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <shatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:40:14 by stan              #+#    #+#             */
/*   Updated: 2024/08/22 10:41:37 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_all_subprocess(t_data *data)
{
	int	i;

	i = 0;
	data->vars.start_time = get_current_ms();
	while (i < data->philo_count)
	{
		data->philo_arr[i].pid = fork();
		if (data->philo_arr[i].pid == 0)
		{
			philo_run(data->philo_arr + i);
			exit(0);
		}
		else if (data->philo_arr[i].pid == -1)
		{
			end_all_subprocess(data);
			delete_data(data);
			exit(1);
		}
		i++;
	}
}

void	end_all_subprocess(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		data->philo_arr[i++].state = S_DEAD;
	i = 0;
	while (i < data->philo_count)
	{
		kill(data->philo_arr[i].pid, SIGKILL);
		++i;
	}
}
