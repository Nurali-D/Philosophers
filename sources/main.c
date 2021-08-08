/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:28:31 by ltulune           #+#    #+#             */
/*   Updated: 2021/08/08 11:28:34 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_vars(pthread_mutex_t *forks, pthread_t *threads, t_philo *ph)
{
	int	i;

	if (forks)
	{
		i = -1;
		while (++i < ph[0].inp->n_philosophers)
			pthread_mutex_destroy(&forks[i]);
		free(forks);
	}
	if (threads)
		free(threads);
	if (ph)
		free(ph);
}

void	error_exit(pthread_mutex_t *forks, pthread_t *threads, t_philo *ph)
{
	printf("malloc error");
	free_vars(forks, threads, ph);
	exit (1);
}

int	main(int argc, char **argv)
{
	pthread_t		*threads;
	t_input			input;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	threads = NULL;
	forks = NULL;
	philos = NULL;
	get_arguments(&input, argv, argc);
	forks = malloc(sizeof(pthread_mutex_t) * input.n_philosophers);
	if (forks == NULL)
		error_exit(forks, threads, philos);
	init_forks(forks, input.n_philosophers);
	threads = malloc(sizeof(pthread_t) * input.n_philosophers);
	if (threads == NULL)
		error_exit(forks, threads, philos);
	philos = malloc(sizeof(t_philo) * input.n_philosophers);
	if (philos == NULL)
		error_exit(forks, threads, philos);
	init_philosophers(philos, &input, forks);
	start_simulation(threads, philos);
	free_vars(forks, threads, philos);
	return (0);
}
