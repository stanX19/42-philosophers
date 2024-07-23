/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:04:17 by shatan            #+#    #+#             */
/*   Updated: 2024/07/23 17:04:20 by shatan           ###   ########.fr       */
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
