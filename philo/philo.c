/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:49:40 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/06 08:52:56 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	*create_thread(int num, t_philo *philo)
{
	pthread_t	*th;
	int			i;

	i = 0;
	th = (pthread_t *)ft_calloc(sizeof(pthread_t), (num + 2));
	if (!th)
		return (NULL);
	while (i < num)
	{
		if (pthread_create(&th[i], NULL, &routine, &philo[i]) != 0)
			return (NULL);
		i++;
		usleep(50);
	}
	pthread_create(&th[i++], NULL, &check_die, philo);
	pthread_create(&th[i], NULL, &check_finish, philo);
	return (th);
}

int	join_thread(pthread_t *th, int num)
{
	int	i;

	i = 0;
	while (i <= num + 1)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	run_thread(int num, t_philo *philo)
{
	pthread_t	*th;

	th = create_thread(num, philo);
	if (!th)
	{
		printf("Something wrong !! Can't create thread...");
		return (1);
	}
	if (join_thread(th, num))
	{
		printf("Something worng !! Can't join thread...");
		return (2);
	}
	free(th);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 || argc > 6 || !check_input(argv))
	{
		printf("Inputs aren't correct. Please check it again !!\n");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
		return (2);
	philo = get_philo(argc, argv);
	if (run_thread(ft_atoi(argv[1]), philo))
	{
		return (3);
	}
	free_philo(philo, argv);
	return (0);
}
