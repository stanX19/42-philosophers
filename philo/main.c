/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:15:30 by stan              #+#    #+#             */
/*   Updated: 2024/07/23 17:03:36 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_to_end(t_data *data)
{
	bool	running;
	int		i;

	running = true;
	while (running)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (data->philo_arr[i].state == S_DEAD)
				running = false;
			i++;
		}
	}
}

int	main(int argc, char *const *argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	start_all_threads(&data);
	wait_to_end(&data);
	end_all_threads(&data);
	delete_data(&data);
	return (0);
}
