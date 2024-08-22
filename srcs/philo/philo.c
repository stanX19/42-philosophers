/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <shatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:04:17 by shatan            #+#    #+#             */
/*   Updated: 2024/08/22 10:48:07 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_observer_func(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (1)
	{
		if (philo_is_dead(philo))
		{
			philo_set_state(philo, S_DEAD);
			return (NULL);
		}
		usleep(1000);
	}
}

void	*philo_run(void *_philo)
{
	t_philo		*philo;
	t_thread	death_observer;

	philo = (t_philo *)_philo;
	philo->last_eat = philo->vars->start_time;
	pthread_create(&death_observer, NULL, death_observer_func, philo);
	if (philo->index % 2 == 0)
		philo_accurate_sleep(philo, philo->vars->eat_time);
	while (philo->state != S_DEAD)
	{
		philo_start_eat(philo);
		philo_set_state(philo, S_THINKING);
	}
	pthread_detach(death_observer);
	return (NULL);
}
