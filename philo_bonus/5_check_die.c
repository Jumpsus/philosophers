/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_check_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:15:09 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 23:04:19 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_die(void *input)
{
	t_philo		*philo;

	philo = (t_philo *)input;
	while (philo->alive)
	{
		if (time_diff(philo->last) >= philo->config.die)
		{
			sem_wait(philo->heart);
			if (philo->alive && time_diff(philo->last) >= philo->config.die)
			{
				philo->alive = 0;
				sem_wait(philo->key);
				printf("%6d %3d died\n", time_diff(philo->start), philo->no);
			}
			sem_post(philo->heart);
		}
	}
	release_fork(philo, philo->fork);
	return (0);
}

void	*check_finish(void *input)
{
	t_philo		*philo;

	philo = (t_philo *)input;
	while (philo->alive)
	{
		if ((philo->config.limit >= 0) && (
				philo->config.count_eat >= philo->config.limit))
		{
			sem_wait(philo->heart);
			philo->alive = 0;
			sem_post(philo->heart);
		}
	}
	release_fork(philo, philo->fork);
	return (0);
}
