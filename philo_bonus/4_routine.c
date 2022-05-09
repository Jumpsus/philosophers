/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:18:15 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/06 10:24:39 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	release_fork(t_philo *philo, sem_t *fork)
{
	if (philo->left)
	{
		sem_post(fork);
		philo->left = 0;
	}
	if (philo->right)
	{
		sem_post(fork);
		philo->right = 0;
	}
}

/* taken left and right fork */
void	r_take_fork(t_philo *philo, sem_t *fork, sem_t *key_card)
{
	int	diff;

	if (philo->alive && !(philo->left))
	{
		sem_wait(fork);
		if (philo->alive)
		{
			diff = time_diff(philo->start);
			check_in(key_card);
			printf("%6d %3d has taken a fork\n", diff, philo->no);
		}
		philo->left = 1;
	}
	if (philo->alive && !(philo->right))
	{
		sem_wait(fork);
		if (philo->alive)
		{
			diff = time_diff(philo->start);
			check_in(key_card);
			printf("%6d %3d has taken a fork\n", diff, philo->no);
		}
		philo->right = 1;
	}
}

void	r_eat(t_philo *philo, sem_t *key_card)
{
	t_time	current;
	int		diff;

	gettimeofday(&current, NULL);
	diff = time_diff(philo->start);
	if (philo->alive)
	{
		sem_wait(philo->heart);
		philo->last = current;
		philo->config.count_eat = philo->config.count_eat + 1;
		check_in(key_card);
		printf("%6d %3d is eating\n", diff, philo->no);
		sem_post(philo->heart);
	}
	usleep((philo->config.eat) * 1000);
}

void	r_sleep(t_philo *philo, sem_t *fork, sem_t *key_card)
{
	int	diff;

	diff = time_diff(philo->start);
	if (philo->alive)
	{
		check_in(key_card);
		printf("%6d %3d is sleeping\n", diff, philo->no);
	}
	release_fork(philo, fork);
	usleep((philo->config.sleep) * 1000);
	diff = time_diff(philo->start);
	if (philo->alive)
	{
		check_in(key_card);
		printf("%6d %3d is thinking\n", diff, philo->no);
	}
}

void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (philo->alive)
	{
		r_take_fork(philo, philo->fork, philo->key);
		r_eat(philo, philo->key);
		r_sleep(philo, philo->fork, philo->key);
	}
	return (0);
}
