/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:24:47 by ltulune           #+#    #+#             */
/*   Updated: 2021/08/08 11:30:11 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_input *inp)
{
	if (inp->n_philosophers <= 0 || inp->time_to_die < 10
		|| inp->time_to_eat < 60 || inp->time_to_sleep < 60
		|| inp->n_must_eat == 0 || inp->n_must_eat < -1)
		return (1);
	return (0);
}

int	check_args_is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strlen(argv[i]))
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

void	get_arguments(t_input *inp, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of arguments!\n");
		exit (1);
	}
	if (check_args_is_digit(argc, argv))
	{
		printf("Invalid arguments!\n");
		exit (1);
	}
	inp->n_philosophers = ft_atoi(argv[1]);
	inp->time_to_die = ft_atoi(argv[2]);
	inp->time_to_eat = ft_atoi(argv[3]);
	inp->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		inp->n_must_eat = ft_atoi(argv[5]);
	else
		inp->n_must_eat = -1;
	if (check_args(inp))
	{
		printf("Invalid arguments!\n");
		exit (1);
	}
}

void	init_forks(pthread_mutex_t *forks, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_init(&forks[i], NULL);
}

void	init_philosophers(t_philo *philos, t_input *inp, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < inp->n_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = i + 1;
		philos[i].inp = inp;
		philos[i].forks = forks;
		philos[i].finish = 0;
		if (i == inp->n_philosophers - 1)
			philos[i].right_fork = 0;
	}
	if (inp->n_philosophers == 1)
	{
		philos[i].left_fork = 0;
		philos[i].right_fork = 0;
	}
}
