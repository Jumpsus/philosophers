/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_check_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:43:13 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 18:28:54 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
void	*check_die(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (philo->alive)
	{
		if (time_diff(philo->last) >= philo->config.die)
		{
			pthread_mutex_lock(philo->heart);
			if (time_diff(philo->last) >= philo->config.die)
			{
				philo->alive = 0;
				printf("%6d %3d died\n", time_diff(philo->start), philo->no);
			}
			pthread_mutex_unlock(philo->heart);
		}
	}
	release_fork(philo);
	return (0);
}
*/
void	genocide(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].config.num)
	{
		philo[i].alive = 0;
		release_fork(&(philo[i]));
		i++;
	}
}

void	*check_die(void	*input)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)input;
	i = 0;
	while (i < philo[0].config.num)
	{
		if (time_diff(philo[i].last) >= philo[i].config.die)
		{	
			pthread_mutex_lock(philo[i].heart);
			if (philo[i].alive && time_diff(
					philo[i].last) >= philo[i].config.die)
			{
				philo[i].alive = 0;
				printf("%6d %3d died\n", time_diff(philo->start), philo[i].no);
			}
			pthread_mutex_unlock(philo[i].heart);
			if (philo[i].alive == 0)
				break ;
		}
		if (++i >= philo[0].config.num)
			i = 0;
	}
	genocide(philo);
	return (0);
}

void	*check_finish(void *input)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)input;
	i = 0;
	while (i < philo[0].config.num)
	{
		if (!(philo[i].alive) || ((philo[i].config.limit >= 0) && (
					philo[i].config.count_eat >= philo[i].config.limit)))
			i++;
		else
			i = 0;
	}
	i = 0;
	while (i < philo[0].config.num)
	{
		philo[i].alive = 0;
		release_fork(&(philo[i]));
		i++;
	}
	return (0);
}
