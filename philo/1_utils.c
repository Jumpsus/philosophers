/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pratanac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:22:54 by pratanac          #+#    #+#             */
/*   Updated: 2022/05/05 09:24:08 by pratanac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + (str[i] - '0');
		i++;
	}
	return (num);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_num(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	time_diff(t_time start)
{
	t_time	c;
	int		diff;

	gettimeofday(&c, NULL);
	diff = 1000 * (c.tv_sec - start.tv_sec) + (
			c.tv_usec - start.tv_usec) / 1000;
	return (diff);
}

void	*ft_calloc(int size, int num)
{
	int		i;
	char	*arr;

	arr = malloc(size * num);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size * num)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}
