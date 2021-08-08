/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:24:36 by ltulune           #+#    #+#             */
/*   Updated: 2021/08/08 11:24:39 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	uint64_t				ret;
	static struct timeval	time;

	if (gettimeofday(&time, 0) < 0)
		return (0);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

void	fix_usleep(uint64_t msec)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(50);
}
