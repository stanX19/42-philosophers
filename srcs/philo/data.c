/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:00:13 by shatan            #+#    #+#             */
/*   Updated: 2024/07/30 14:47:50 by shatan           ###   ########.fr       */
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

static t_mutex	*create_mutex_arr(int count)
{
	t_mutex *ret;

	ret = (t_mutex *)malloc(sizeof(t_mutex) * count);
	int	i;
	
	i = 0;
	while (i < count)
	{
		pthread_mutex_init(ret + i, NULL);
		i++;
	}
	return ret;
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
	data->fork_arr = create_mutex_arr(data->philo_count);
	data->philo_arr = create_philo_arr(data->philo_count, &data->vars,
			data->fork_arr);
	if (errno)
	{
		delete_data(data);
		return (1);
	}
	return (0);
}