/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:09:51 by shatan            #+#    #+#             */
/*   Updated: 2024/07/30 14:41:47 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_set_state(t_philo *philo, t_state new_state)
{
	if (philo->state == new_state || philo->state == S_DEAD)
		return ;
	philo->state = new_state;
	if (new_state == S_EATING)
		philo_announce_action(philo, "is eating");
	else if (new_state == S_THINKING)
		philo_announce_action(philo, "is thinking");
	else if (new_state == S_SLEEPING)
		philo_announce_action(philo, "is sleeping");
	else if (new_state == S_DEAD)
		philo_announce_action(philo, "died");
}