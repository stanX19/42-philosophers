/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_eat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:23:41 by shatan            #+#    #+#             */
/*   Updated: 2024/08/02 14:30:52 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_start_eat(t_philo *philo)
{
	sem_wait(philo->vars->forks);
	philo_announce_action(philo, "has taken a fork");
	sem_wait(philo->vars->forks);
	philo_announce_action(philo, "has taken a fork");
	philo->eat_count++;
	philo->last_eat = get_current_ms();
	philo_set_state(philo, S_EATING);
	philo_accurate_sleep(philo, philo->vars->eat_time);
	sem_post(philo->vars->forks);
	sem_post(philo->vars->forks);
	philo_set_state(philo, S_SLEEPING);
	philo_accurate_sleep(philo, philo->vars->sleep_time);
}