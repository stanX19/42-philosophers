/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shatan <shatan@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:07:25 by shatan            #+#    #+#             */
/*   Updated: 2024/08/02 14:24:47 by shatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	ret_is_invalid(unsigned long long ret, long digit,
	unsigned long long limit)
{
	unsigned long long	ret_max;
	long				digit_max;

	ret_max = limit / 10;
	digit_max = limit % 10;
	return (ret > ret_max || (ret == ret_max && digit > digit_max));
}

static bool	get_digit(char **str, long *val)
{
	char	c;

	c = **str;
	if (c >= '0' && c <= '9')
	{
		*val = c - '0';
		(*str)++;
		return (true);
	}
	return (false);
}

static bool	ft_isspace(char c)
{
	return (c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f'
		|| c == ' ');
}

unsigned long long	ft_atou(const char *nptr, unsigned long long limit)
{
	char				*str;
	long				digit;
	unsigned long long	ret;

	str = (char *)nptr;
	while (ft_isspace(*str))
		++str;
	ret = 0;
	digit = -1;
	while (get_digit(&str, &digit))
	{
		if (ret_is_invalid(ret, digit, limit))
		{
			errno = ERANGE;
			return (ULLONG_MAX);
		}
		else
			ret = (ret * 10) + digit;
	}
	if (digit < 0 || *str != '\0')
		errno = EINVAL;
	return (ret);
}
