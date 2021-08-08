/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:23:03 by ltulune           #+#    #+#             */
/*   Updated: 2021/08/08 12:09:37 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->forks[ph->left_fork]);
	printf(FORK1, get_time() - ph->start_time, ph->id);
	pthread_mutex_lock(&ph->forks[ph->right_fork]);
	printf(FORK2, get_time() - ph->start_time, ph->id);
	printf(EAT, get_time() - ph->start_time, ph->id);
}

void	*eat_think_sleep(t_philo *ph)
{
	int				i;

	i = 0;
	if (ph->id % 2 != 0)
		fix_usleep(ph->inp->time_to_eat / 2);
	while (1)
	{
		get_forks_eat(ph);
		fix_usleep(ph->inp->time_to_eat);
		pthread_mutex_unlock(&ph->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->forks[ph->right_fork]);
		ph->last_meal_time = get_time();
		printf(SLEEP, get_time() - ph->start_time, ph->id);
		fix_usleep(ph->inp->time_to_sleep);
		printf(THINK, get_time() - ph->start_time, ph->id);
		if (ph->inp->n_must_eat != -1 && ph->inp->n_must_eat == ++i)
			break ;
	}
	ph->finish = 1;
	return (NULL);
}

void	check_death(t_philo *philos)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (1)
	{
		if (philos[i].finish == 1)
			philos[i].finish = ++c;
		if (c == philos[i].inp->n_philosophers && philos[i].inp->n_must_eat > 0)
			break ;
		if (!philos[i].finish && (int)(get_time() - philos[i].last_meal_time) >
		philos[i].inp->time_to_die)
		{
			printf(DEATH, get_time() - philos[i].start_time, philos[i].id);
			break ;
		}
		if (i == philos[i].inp->n_philosophers - 1)
			i = 0;
		else
			i++;
		usleep(500);
	}
}

void	start_simulation(pthread_t *threads, t_philo *philos)
{
	int			i;
	uint64_t	start_time;

	start_time = get_time();
	i = -1;
	while (++i < philos[0].inp->n_philosophers)
	{
		philos[i].start_time = start_time;
		philos[i].last_meal_time = start_time;
		pthread_create(&threads[i], NULL, (void *)eat_think_sleep, &philos[i]);
	}
	check_death(philos);
	i = -1;
	while (++i < philos[0].inp->n_philosophers)
		pthread_detach(threads[i]);
}
