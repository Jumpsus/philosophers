/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_free_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:36:05 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 09:37:14 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_fork(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(philo[i].l_fork);
		pthread_mutex_destroy(philo[i].heart);
		i++;
	}
	free(philo->l_fork);
	free(philo->heart);
}

void	free_philo(t_philo *philo, char **argv)
{
	destroy_fork(philo, ft_atoi(argv[1]));
	free(philo);
}
