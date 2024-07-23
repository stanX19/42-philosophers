/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:15:30 by stan              #+#    #+#             */
/*   Updated: 2024/07/23 17:00:17 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_run(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (philo->state == S_PENDING)
		;
	printf("philo %i started\n", philo->index);
	philo->last_eat = philo->vars->start_time;
	while (philo->state != S_DEAD)
	{
		philo_set_state(philo, S_THINKING);
		usleep(1000 * (100 - (get_time_passed(philo)) % 100));
		if (philo_is_dead(philo))
			philo_set_state(philo, S_DEAD);
	}
	return (NULL);
}

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
		data->philo_arr[i++].state = S_THINKING;
}

void	end_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
		data->philo_arr[i++].state = S_DEAD;
	i = 0;
	while (i < data->philo_count)
		pthread_join(data->thread_arr[i++], NULL);
}

void	wait_to_end(t_data *data)
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
