/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:34:49 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 16:47:28 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_time;

typedef struct s_rouconf
{
	int	num;
	int	die;
	int	eat;
	int	sleep;
	int	limit;
	int	count_eat;
}	t_rouconf;

typedef struct s_philo
{
	int					alive;
	int					no;
	int					left;
	int					right;
	t_rouconf			config;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*heart;
	t_time				start;
	t_time				last;
}	t_philo;

/* 1_utils.c */
int				ft_atoi(char *str);
int				check_num(char *str);
int				check_input(char **argv);
int				time_diff(t_time start);
void			*ft_calloc(int size, int num);

/* 2_config.c */
t_philo			*get_philo(int argc, char **argv);

/* 3_free_philo.c */
void			free_philo(t_philo *philo, char **argv);

/* 4_routine.c */
void			release_fork(t_philo *philo);
void			*routine(void *input);

/* 5_check_die.c */
void			*check_die(void *input);
void			*check_finish(void *input);
#endif
