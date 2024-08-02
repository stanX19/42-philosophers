/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:10:39 by shatan            #+#    #+#             */
/*   Updated: 2024/08/02 18:04:01 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>

# ifdef __APPLE__
#  define TIME_FMT_STR "%llu"
typedef u_int64_t		t_time;
# else
#  define TIME_FMT_STR "%lu"
typedef suseconds_t		t_time;
# endif
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef enum e_status
{
	S_EATING,
	S_THINKING,
	S_SLEEPING,
	S_DEAD,
	S_PENDING,
}						t_state;

typedef struct s_vars
{
	t_time				death_time;
	t_time				eat_time;
	t_time				sleep_time;
	t_time				start_time;
	int					eat_needed;
	sem_t				*forks;
	sem_t				*print;
	sem_t				*dead;
	sem_t				*completed;
}						t_vars;

typedef struct s_philo
{
	int					eat_count;
	int					index;
	t_state				state;
	t_time				last_eat;
	t_vars				*vars;
	pid_t				pid;
}						t_philo;

typedef struct s_data
{
	int					philo_count;
	bool				running;
	t_vars				vars;
	t_philo				*philo_arr;
}						t_data;

unsigned long long		ft_atou(const char *nptr, unsigned long long limit);
t_time					get_current_ms(void);
t_time					get_time_passed(t_philo *philo);
t_time					get_hungry_time(t_philo *philo);
bool					philo_is_dead(t_philo *philo);
void					philo_announce_action(t_philo *philo, const char *msg);
void					philo_accurate_sleep(t_philo *philo, t_time time);
void					philo_set_state(t_philo *philo, t_state new_state);
void					philo_run(t_philo *philo);
void					delete_data(t_data *data);
int						init_data(t_data *data, int argc, char *const *argv);
void					start_all_subprocess(t_data *data);
void					end_all_subprocess(t_data *data);
void					philo_start_eat(t_philo *philo);
#endif // PHILO
