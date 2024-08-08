/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <shatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:00:13 by shatan            #+#    #+#             */
/*   Updated: 2024/08/08 14:21:55 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	delete_data(t_data *data)
{
	if (data->philo_arr)
		free(data->philo_arr);
	if (data->vars.forks)
		sem_unlink("/forks");
	if (data->vars.print)
		sem_unlink("/print");
	if (data->vars.completed)
		sem_unlink("/completed");
	if (data->vars.dead)
		sem_unlink("/dead");
}

static t_philo	*create_philo_arr(int count, t_vars *vars)
{
	t_philo	*ret;
	int		i;

	if (count == 0 || vars == NULL)
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
		ret[i].pid = 0;
		i++;
	}
	return (ret);
}

sem_t	*open_semaphore(const char *name, int n)
{
	int		original_errno;
	sem_t	*ret;

	original_errno = errno;
	errno = 0;
	ret = sem_open(name, O_CREAT | O_EXCL, 0644, n);
	if (errno)
	{
		sem_unlink(name);
		ret = sem_open(name, O_CREAT | O_EXCL, 0644, n);
	}
	errno = original_errno;
	return (ret);
}

int	init_data(t_data *data, int argc, char *const *argv)
{
	errno = 0;
	data->philo_count = ft_atou(argv[1], INT_MAX);
	data->vars.death_time = (t_time)ft_atou(argv[2], ULLONG_MAX);
	data->vars.eat_time = (t_time)ft_atou(argv[3], ULLONG_MAX);
	data->vars.sleep_time = (t_time)ft_atou(argv[4], ULLONG_MAX);
	data->vars.start_time = 0;
	data->vars.eat_needed = -1;
	if (argc == 6)
		data->vars.eat_needed = ft_atou(argv[5], LLONG_MAX);
	data->philo_arr = create_philo_arr(data->philo_count, &data->vars);
	data->vars.forks = open_semaphore("/forks", data->philo_count);
	data->vars.print = open_semaphore("/print", 1);
	data->vars.dead = open_semaphore("/dead", 0);
	data->vars.completed = open_semaphore("/completed", 0);
	if (errno)
	{
		delete_data(data);
		return (1);
	}
	return (0);
}
