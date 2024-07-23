#include "philo.h"

t_time	get_time_passed(t_philo *philo)
{
	return (get_current_ms() - philo->vars->start_time);
}

t_time	get_last_eat(t_philo *philo)
{
	return (get_current_ms() - philo->last_eat);
}

bool	philo_is_dead(t_philo *philo)
{
	return (philo->state == S_DEAD ||
		get_last_eat(philo) > philo->vars->death_time);
}

void	philo_set_state(t_philo *philo, t_state new_state)
{
	philo->state = new_state;
	printf(STATE_FMT, get_time_passed(philo), philo->index);
	if (new_state == S_EATING)
		printf("is eating\n");
	else if (new_state == S_THINKING)
		printf("is thinking\n");
	else if (new_state == S_SLEEPING)
		printf("is sleeping\n");
	else if (new_state == S_DEAD)
		printf("died\n");
}
