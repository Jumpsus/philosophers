/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:11:00 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/06 10:37:16 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SEM_NAME "/fork"
# define KEY_C "/keycard"

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
	int			alive;
	int			no;
	int			left;
	int			right;
	sem_t		*key;
	sem_t		*fork;
	sem_t		*heart;
	t_rouconf	config;
	t_time		start;
	t_time		last;
}	t_philo;

/* 1_utils.c */
int				ft_atoi(char *str);
int				check_num(char *str);
int				check_input(char **argv);
int				time_diff(t_time start);
void			*ft_calloc(int size, int num);

/* 3_config.c */
t_philo			*get_philo(int argc, char **argv);

/* 4_routine.c */
void			release_fork(t_philo *philo, sem_t *fork);
void			*routine(void *input);

/* 5_check_die.c */
void			*check_die(void *input);
void			*check_finish(void *input);

/* 2_utils_bonus.c */
char			*ft_itoa(int num);
void			check_in(sem_t *key_card);
void			genocide(pid_t *pid, int num);
sem_t			*create_sem(int num, char *name);
#endif
