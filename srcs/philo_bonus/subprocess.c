#include "philo_bonus.h"

void	start_all_subprocess(t_data *data)
{
	int	i;

	i = 0;
	data->vars.start_time = get_current_ms();
	while (i < data->philo_count)
	{
		data->philo_arr[i].pid = fork();
		if (data->philo_arr[i].pid == 0)
		{
			philo_run(data->philo_arr + i);
			exit(0);
		}
		else if (data->philo_arr[i].pid == -1)
		{
			end_all_subprocess(data);
			delete_data(data);
			exit(1);
		}
		i++;
	}
}

void	end_all_subprocess(t_data *data)
{
	// kill(0, SIGKILL);
	// (void)data;
	int	i;

	i = 0;
	while (i < data->philo_count)
		data->philo_arr[i++].state = S_DEAD;
	i = 0;
	while (i < data->philo_count)
	{
		kill(data->philo_arr[i].pid, SIGKILL);
		++i;
	}
}