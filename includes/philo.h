#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	char		*name;
	unsigned	left_fork;
	unsigned	right_fork;
}				t_philo;
 
typedef struct s_table
{
	pthread_mutex_t	*forks;
}				t_table;
 
typedef struct philosopher_args_tag {
	t_philo	*philosopher;
	t_table	*table;
} philosopher_args_t;

#endif