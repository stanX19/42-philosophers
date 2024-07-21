/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <shatan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:10:39 by shatan            #+#    #+#             */
/*   Updated: 2024/07/21 21:49:34 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifdef __APPLE__
  typedef u_int64_t t_time;
# else
  typedef suseconds_t t_time;
# endif
typedef pthread_mutex_t t_mutex;
typedef pthread_t t_thread;

typedef enum e_status
{
	S_EATING,
	S_THINKING,
	S_SLEEPING,
	S_DEAD,
}	t_status;

typedef struct s_vars
{
	t_time				death_time;
	t_time				eat_time;
	t_time				sleep_time;
	t_time				start_time;
	long long			eat_needed;
}	t_vars;


typedef struct s_philo
{
	t_status	status;
	t_time		last_eat;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_vars		*vars;
}	t_philo;


typedef struct s_data
{
	int					philo_count;
	t_vars				vars;
	t_thread			*thread_arr;
	t_philo				*philo_arr;
	t_mutex				*fork_arr;
}						t_data;

unsigned long long	ft_atou(const char *nptr, unsigned long long limit);

#endif // PHILO
