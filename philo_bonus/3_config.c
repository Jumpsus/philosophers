/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:09:40 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 11:10:37 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* do this only after you check there is no surprise in input*/
t_rouconf	get_routine_config(int argc, char **argv)
{
	t_rouconf	config;

	config.num = ft_atoi(argv[1]);
	config.die = ft_atoi(argv[2]);
	config.eat = ft_atoi(argv[3]);
	config.sleep = ft_atoi(argv[4]);
	config.count_eat = 0;
	if (argc == 5)
		config.limit = -1;
	else
		config.limit = ft_atoi(argv[5]);
	return (config);
}

t_philo	*fill_philo(int num, t_rouconf config)
{
	t_philo		*philo;
	int			i;
	t_time		start_time;

	i = 0;
	gettimeofday(&start_time, NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (!philo)
		return (NULL);
	while (i < num)
	{
		philo[i].alive = 1;
		philo[i].no = i + 1;
		philo[i].left = 0;
		philo[i].right = 0;
		philo[i].config = config;
		philo[i].start = start_time;
		philo[i].last = start_time;
		i++;
	}
	return (philo);
}

/*need to free philo and fork after use*/
t_philo	*get_philo(int argc, char **argv)
{
	t_rouconf	config;
	t_philo		*philo;

	config = get_routine_config(argc, argv);
	philo = fill_philo(ft_atoi(argv[1]), config);
	return (philo);
}
