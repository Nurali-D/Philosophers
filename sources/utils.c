/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:27:40 by ltulune           #+#    #+#             */
/*   Updated: 2021/08/08 11:28:20 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}

static int	ft_isspace(char b)
{
	if (b == ' ' || b == '\t' || b == '\n' || b == '\v' || b == '\f'
		|| b == '\r')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	put_sign(long int b, int s)
{
	if (s == -1)
	{
		if (b > 2147483648)
			return (0);
		else
			return (s * b);
	}
	if (b > 2147483647)
		return (-1);
	return (b);
}

int	ft_atoi(const char *nptr)
{
	long int	buf;
	int			sign;

	buf = 0;
	sign = 1;
	while (*nptr)
	{
		if (ft_isspace(*nptr))
			;
		else if (*nptr == '+' && ft_isdigit(*(nptr + 1)))
			sign = 1;
		else if (*nptr == '-' && ft_isdigit(*(nptr + 1)))
			sign = -1;
		else if (!(ft_isdigit(*nptr)))
			return (0);
		else if (ft_isdigit(*nptr))
			buf = buf * 10 + *nptr - '0';
		if (buf > 2147483648
			|| (ft_isdigit(*nptr) && !(ft_isdigit(*(nptr + 1)))))
			return (put_sign(buf, sign));
		nptr++;
	}
	return (put_sign(buf, sign));
}
