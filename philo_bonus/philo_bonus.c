/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:21:45 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/06 10:41:55 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	small_thread(t_philo *philo, pthread_t *th)
{
	if (pthread_create(&th[0], NULL, &routine, philo) != 0)
		return (1);
	if (pthread_create(&th[1], NULL, &check_die, philo) != 0)
		return (2);
	if (pthread_create(&th[2], NULL, &check_finish, philo) != 0)
		return (3);
	if (pthread_join(th[0], NULL) != 0)
		return (4);
	if (pthread_join(th[1], NULL) != 0)
		return (5);
	if (pthread_join(th[2], NULL) != 0)
		return (6);
	return (0);
}

int	run_thread(t_philo *philo)
{
	pthread_t	*th;
	char		*id;

	th = (pthread_t *)ft_calloc(sizeof(pthread_t), 3);
	if (!th)
		return (1);
	id = ft_itoa(philo->no - 1);
	sem_unlink(id);
	philo->heart = sem_open(id, O_CREAT, S_IRUSR | S_IWUSR, 1);
	philo->fork = sem_open(SEM_NAME, O_RDWR);
	philo->key = sem_open(KEY_C, O_RDWR);
	if (small_thread(philo, th))
		return(2);
	sem_close(philo->heart);
	sem_close(philo->fork);
	sem_close(philo->key);
	sem_unlink(id);
	free(id);
	free(th);
	return (0);
}

void	multi_process(int num, t_philo *philo)
{
	pid_t	*pid;
	int		i;

	i = 0;
	pid = (pid_t *)ft_calloc(sizeof(pid_t), num);
	while (i < num)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			run_thread(&philo[i]);
			break ;
		}
		i++;
	}
	if (pid[num - 1] != 0)
	{
		genocide(pid, num);
	}
	free(pid);
}

int	run_fork(int num, t_philo *philo)
{
	sem_t	*my_fork;
	sem_t	*key_card;

	my_fork = create_sem(num, SEM_NAME);
	key_card = create_sem(1, KEY_C);
	if (!my_fork || !key_card)
		return (1);
	multi_process(num, philo);
	sem_unlink(SEM_NAME);
	sem_unlink(KEY_C);
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
	if (run_fork(ft_atoi(argv[1]), philo))
	{
		return (3);
	}
	free(philo);
	return (0);
}
