/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_utils_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:20:37 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/06 10:40:45 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_mem(int num)
{
	int	i;

	i = 0;
	while (num > 9)
	{
		num = num / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int num)
{
	char	*str;
	int		i;

	if (num < 0)
		return (NULL);
	i = get_mem(num);
	str = malloc(sizeof(char) * (i + 1));
	str[i--] = 0;
	while (num > 9)
	{
		str[i] = (num % 10) + '0';
		num = num / 10;
		i--;
	}
	str[i] = num + '0';
	return (str);
}

void	check_in(sem_t *key_card)
{
	sem_wait(key_card);
	sem_post(key_card);
}

void	genocide(pid_t *pid, int num)
{
	int	i;

	i = 0;
	if (waitpid(0, NULL, 0))
	{
		i = 0;
		while (i < num)
		{
			kill(pid[i], SIGKILL);
			i++;
		}
	}
}

sem_t	*create_sem(int num, char *name)
{
	sem_t	*my_sem;

	sem_unlink(name);
	my_sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, num);
	if (my_sem == SEM_FAILED)
	{
		printf("Failed to open semaphore");
		return (NULL);
	}
	if (sem_close(my_sem) < 0)
	{
		printf("Failed to close semaphore");
		sem_unlink(name);
		return (NULL);
	}
	return (my_sem);
}
