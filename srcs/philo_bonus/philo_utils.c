/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:26:44 by shatan            #+#    #+#             */
/*   Updated: 2024/08/23 15:56:21 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->vars->print);
	printf(TIME_FMT_STR " %i %s\n", time_passed - time_passed % 100, philo->index, msg);
	sem_post(philo->vars->print);
}

void	philo_accurate_sleep(t_philo *philo, t_time time)
{
	t_time	end;

	end = get_time_passed(philo) + time;
	end -= end % 100;
	while (get_time_passed(philo) < end)
		usleep(100);
}
