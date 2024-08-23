/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:15:30 by stan              #+#    #+#             */
/*   Updated: 2024/08/23 16:39:30 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_to_end(t_data *data)
{
	bool	running;
	int		complete_count;
	int		i;

	running = true;
	while (running)
	{
		i = 0;
		complete_count = 0;
		while (i < data->philo_count)
		{
			if (data->philo_arr[i].state == S_DEAD)
				running = false;
			if (data->vars.eat_needed != -1
				&& data->philo_arr[i].eat_count >= data->vars.eat_needed)
				complete_count++;
			i++;
		}
		if (complete_count == data->philo_count)
			running = false;
	}
}

static inline int	handle_case_0(t_data *data)
{
	delete_data(data);
	return (0);
}

static inline int	handle_case_1(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->vars.death_time * 1000);
	printf(TIME_FMT_STR " 1 died\n", data->vars.death_time);
	delete_data(data);
	return (0);
}

int	main(int argc, char *const *argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || init_data(&data, argc, argv))
	{
		printf("Error\n");
		return (1);
	}
	if (data.philo_count == 0)
		return (handle_case_0(&data));
	if (data.philo_count == 1)
		return (handle_case_1(&data));
	start_all_threads(&data);
	wait_to_end(&data);
	end_all_threads(&data);
	delete_data(&data);
	return (0);
}
