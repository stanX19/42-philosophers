/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:15:30 by stan              #+#    #+#             */
/*   Updated: 2024/08/23 16:42:14 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*wait_for_death(void *_data)
{
	t_data	*data;

	data = (t_data *)_data;
	sem_wait(data->vars.dead);
	data->running = false;
	return (NULL);
}

static void	*wait_for_complete(void *_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)_data;
	i = 0;
	while (i < data->philo_count)
	{
		sem_wait(data->vars.completed);
		i++;
	}
	data->running = false;
	return (NULL);
}

static void	wait_to_end(t_data *data)
{
	t_thread	death_observer;
	t_thread	complete_observer;

	pthread_create(&death_observer, NULL, wait_for_death, data);
	pthread_create(&complete_observer, NULL, wait_for_complete, data);
	data->running = true;
	while (data->running)
		;
	pthread_detach(complete_observer);
	pthread_detach(death_observer);
	usleep(20000);
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
	{
		delete_data(&data);
		return (0);
	}
	if (data.philo_count == 1)
		return (handle_case_1(&data));
	start_all_subprocess(&data);
	wait_to_end(&data);
	end_all_subprocess(&data);
	delete_data(&data);
	return (0);
}
