/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_eat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:23:41 by shatan            #+#    #+#             */
/*   Updated: 2024/08/02 14:10:26 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_announce_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo_announce_action(philo, "has taken a fork");
	philo->eat_count++;
	philo->last_eat = get_current_ms();
	philo_set_state(philo, S_EATING);
	philo_accurate_sleep(philo, philo->vars->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo_set_state(philo, S_SLEEPING);
	philo_accurate_sleep(philo, philo->vars->sleep_time);
}