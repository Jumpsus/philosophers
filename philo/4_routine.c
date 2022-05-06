/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:37:22 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 18:03:33 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	release_fork(t_philo *philo)
{
	if (philo->left)
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->left = 0;
	}
	if (philo->right)
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->right = 0;
	}
}

/* taken left and right fork */
void	r_take_fork(t_philo *philo)
{
	int	diff;

	if (philo->alive && !(philo->left))
	{
		pthread_mutex_lock(philo->l_fork);
		if (philo->alive)
		{
			diff = time_diff(philo->start);
			printf("%6d %3d has taken a fork\n", diff, philo->no);
		}
		philo->left = 1;
	}
	if (philo->alive && !(philo->right))
	{
		pthread_mutex_lock(philo->r_fork);
		if (philo->alive)
		{
			diff = time_diff(philo->start);
			printf("%6d %3d has taken a fork\n", diff, philo->no);
		}
		philo->right = 1;
	}
}

void	r_eat(t_philo *philo)
{
	t_time	current;
	int		diff;

	gettimeofday(&current, NULL);
	pthread_mutex_lock(philo->heart);
	diff = time_diff(philo->start);
	if (philo->alive)
	{
		philo->last = current;
		philo->config.count_eat = philo->config.count_eat + 1;
		printf("%6d %3d is eating\n", diff, philo->no);
	}
	pthread_mutex_unlock(philo->heart);
	usleep((philo->config.eat) * 1000);
}

void	r_sleep(t_philo *philo)
{
	int	diff;

	diff = time_diff(philo->start);
	if (philo->alive)
		printf("%6d %3d is sleeping\n", diff, philo->no);
	release_fork(philo);
	usleep((philo->config.sleep) * 1000);
	diff = time_diff(philo->start);
	if (philo->alive)
		printf("%6d %3d is thinking\n", diff, philo->no);
}

void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (philo->alive)
	{
		r_take_fork(philo);
		r_eat(philo);
		r_sleep(philo);
	}
	return (0);
}
