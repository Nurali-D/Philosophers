/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:30:24 by ltulune           #+#    #+#             */
/*   Updated: 2021/08/08 11:31:00 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define FORK1	"%lld %d has taken a fork1 \n"
# define FORK2	"%lld %d has taken a fork2 \n"
# define EAT	"%lld %d is eating \n"
# define SLEEP	"%lld %d is sleeping \n"
# define THINK	"%lld %d is thinking \n"
# define DEATH	"%lld %d died\n"

typedef struct s_input
{
	int	n_philosophers;
	int	n_must_eat;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}				t_input;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				finish;
	uint64_t		start_time;
	uint64_t		last_meal_time;
	t_input			*inp;
	pthread_mutex_t	*forks;
}				t_philo;

int			ft_atoi(const char *nptr);
void		fix_usleep(uint64_t msec);
uint64_t	get_time(void);
void		get_arguments(t_input *inp, char **argv, int argc);
void		init_forks(pthread_mutex_t *forks, int n);
void		init_philosophers(t_philo *philos, t_input *inp,
				pthread_mutex_t *forks);
void		start_simulation(pthread_t *threads, t_philo *philos);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);

#endif
