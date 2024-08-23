/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:46:22 by stan              #+#    #+#             */
/*   Updated: 2024/08/23 15:56:07 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	get_time_passed(t_philo *philo)
{
	return (get_current_ms() - philo->vars->start_time);
}

t_time	get_hungry_time(t_philo *philo)
{
	return (get_current_ms() - philo->last_eat);
}

bool	philo_is_dead(t_philo *philo)
{
	return (philo->state == S_DEAD
		|| get_hungry_time(philo) >= philo->vars->death_time + 5);
}

void	philo_announce_action(t_philo *philo, const char *msg)
{
	t_time time_passed;

	time_passed = get_time_passed(philo);
	printf(TIME_FMT_STR " %i %s\n", time_passed - time_passed % 100, philo->index, msg);
}

void	philo_accurate_sleep(t_philo *philo, t_time time)
{
	t_time	start;
	t_time	wait;

	start = get_current_ms();
	wait = time - get_time_passed(philo) % 100;
	while (get_current_ms() - start < wait)
		usleep(100);
}
