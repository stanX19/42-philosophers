/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <shatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:04:17 by shatan            #+#    #+#             */
/*   Updated: 2024/08/08 14:24:13 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*observer_func(void *_philo)
{
	t_philo	*philo;
	bool	registered_done;

	philo = (t_philo *)_philo;
	registered_done = false;
	while (1)
	{
		if (philo_is_dead(philo))
		{
			philo_set_state(philo, S_DEAD);
			sem_post(philo->vars->dead);
			return (NULL);
		}
		if (!registered_done && philo->vars->eat_needed != -1
			&& philo->eat_count >= philo->vars->eat_needed)
		{
		// sem_wait(philo->vars->print);
		// printf("cond %i %i %i\n", !registered_done, philo->vars->eat_needed != -1
		// 	,philo->eat_count >= philo->vars->eat_needed);
		// sem_post(philo->vars->print);
			sem_post(philo->vars->completed);
			registered_done = true;
		}
		usleep(1000);
	}
}

void	philo_run(t_philo *philo)
{
	t_thread	observer;

	philo->last_eat = philo->vars->start_time;
	pthread_create(&observer, NULL, observer_func, philo);
	if (philo->index % 2 == 0)
		philo_accurate_sleep(philo, philo->vars->eat_time);
	while (philo->state != S_DEAD)
	{
		philo_start_eat(philo);
		philo_set_state(philo, S_THINKING);
	}
	pthread_detach(observer);
}
