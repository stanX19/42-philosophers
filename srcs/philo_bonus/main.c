/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <shatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:15:30 by stan              #+#    #+#             */
/*   Updated: 2024/08/08 14:24:43 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void *wait_for_death(void *_data)
{
	t_data	*data;
	
	data = (t_data *)_data;
	sem_wait(data->vars.dead);
	printf("\ndead\n");
	data->running = false;
	return NULL;
}

static void *wait_for_complete(void *_data)
{
	t_data	*data;

	data = (t_data *)_data;
	int	i;
	
	i = 0;
	while (i < data->philo_count)
	{
		sem_wait(data->vars.completed);
		i++;
	}
	data->running = false;
	return NULL;
}

static void	wait_to_end(t_data *data)
{
	t_thread death_observer;
	t_thread complete_observer;

	pthread_create(&death_observer, NULL, wait_for_death, data);
	pthread_create(&complete_observer, NULL, wait_for_complete, data);
	data->running = true;
	while (data->running)
		;
	pthread_detach(complete_observer);
	pthread_detach(death_observer);
	usleep(20000);
}

int	main(int argc, char *const *argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	start_all_subprocess(&data);
	wait_to_end(&data);
	end_all_subprocess(&data);
	delete_data(&data);
	return (0);
}
