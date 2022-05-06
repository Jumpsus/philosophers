/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:24:18 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 16:11:10 by pratanac         ###   ########.fr       */
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

/* create mutex fork and heart*/
pthread_mutex_t	*create_fork(char **argv)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(
				pthread_mutex_t) * ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&(fork[i]), NULL);
		i++;
	}
	return (fork);
}

t_philo	*fill_philo(int num, pthread_mutex_t *fork,
		pthread_mutex_t *heart, t_rouconf config)
{
	t_philo	*philo;
	int		i;
	t_time	start_time;

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
		philo[i].l_fork = &(fork[i]);
		philo[i].r_fork = &(fork[(i + 1) % num]);
		philo[i].heart = &(heart[i]);
		philo[i].start = start_time;
		philo[i].last = start_time;
		i++;
	}
	return (philo);
}

/*need to free philo and fork after use*/
t_philo	*get_philo(int argc, char **argv)
{
	t_rouconf		config;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*heart;

	fork = create_fork(argv);
	heart = create_fork(argv);
	config = get_routine_config(argc, argv);
	philo = fill_philo(ft_atoi(argv[1]), fork, heart, config);
	return (philo);
}
