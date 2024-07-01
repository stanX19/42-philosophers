#include "philo.h"

int	init_data(t_data *data, int argc, char *const *argv)
{
	data->philo_count = ft_atou(argv[1], ULLONG_MAX);
	data->death_time = (u_int64_t)ft_atou(argv[2], ULLONG_MAX);
	data->eat_time = (u_int64_t)ft_atou(argv[3], ULLONG_MAX);
	data->sleep_time = (u_int64_t)ft_atou(argv[4], ULLONG_MAX);
	data->eat_needed = -1;
	if (argc == 6)
		data->eat_needed = ft_atou(argv[5], LLONG_MAX);
	if (errno)
		return (1);
	return (0);
}

int	main(int argc, char *const *argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	return (0);
}
