/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:15:30 by stan              #+#    #+#             */
/*   Updated: 2024/07/23 16:38:49 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delete_data(t_data *data)
{
	if (data->fork_arr)
		free(data->fork_arr);
	if (data->thread_arr)
		free(data->thread_arr);
	if (data->philo_arr)
		free(data->philo_arr);
}

static t_philo	*create_philo_arr(int count, t_vars *vars, t_mutex *forks)
{
	t_philo	*ret;
	int		i;

	if (count == 0 || vars == NULL || forks == NULL)
		return (NULL);
	ret = (t_philo *)malloc(sizeof(t_philo) * count);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ret[i].index = i + 1;
		ret[i].eat_count = 0;
		ret[i].state = S_PENDING;
		ret[i].last_eat = 0;
		ret[i].vars = vars;
		ret[i].left_fork = forks + i;
		ret[i].right_fork = forks + (i + 1) % count;
		i++;
	}
	return (ret);
}

int	init_data(t_data *data, int argc, char *const *argv)
{
	data->philo_count = ft_atou(argv[1], INT_MAX);
	data->vars.death_time = (t_time)ft_atou(argv[2], ULLONG_MAX);
	data->vars.eat_time = (t_time)ft_atou(argv[3], ULLONG_MAX);
	data->vars.sleep_time = (t_time)ft_atou(argv[4], ULLONG_MAX);
	data->vars.start_time = 0;
	data->vars.eat_needed = -1;
	if (argc == 6)
		data->vars.eat_needed = ft_atou(argv[5], LLONG_MAX);
	data->thread_arr = (t_thread *)malloc(sizeof(t_thread) * data->philo_count);
	data->fork_arr = (t_mutex *)malloc(sizeof(t_mutex) * data->philo_count);
	data->philo_arr = create_philo_arr(data->philo_count, &data->vars,
			data->fork_arr);
	if (errno)
	{
		delete_data(data);
		return (1);
	}
	return (0);
}



t_time	get_time_passed(t_philo *philo)
{
	return (get_current_ms() - philo->vars->start_time);
}

t_time	get_last_eat(t_philo *philo)
{
	return (get_current_ms() - philo->last_eat);
}

bool	philo_is_dead(t_philo *philo)
{
	return (philo->state == S_DEAD ||
		get_last_eat(philo) > philo->vars->death_time);
}

void	philo_set_state(t_philo *philo, t_state new_state)
{
	philo->state = new_state;
	printf(STATE_FMT, get_time_passed(philo), philo->index);
	if (new_state == S_EATING)
		printf("is eating\n");
	else if (new_state == S_THINKING)
		printf("is thinking\n");
	else if (new_state == S_SLEEPING)
		printf("is sleeping\n");
	else if (new_state == S_DEAD)
		printf("died\n");
}

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
