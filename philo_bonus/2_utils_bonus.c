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
