/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:37:05 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/27 15:06:18 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

/**
 * ft_atoi - Convert String To integer
 * @num: The variable number holds the value converted using atoi.
 * @sign : The variable sign holds the sign of the number.
 * Return: (sign * num) if succeeded or -2
 */

int	ft_atoi(char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		if (sign == 1 && num > INT_MAX)
			return (-2);
		else if (sign == -1 && num > -(long long)INT_MIN)
			return (-2);
		num = num * 10 + (*str++ - '0');
	}
	if (*str || num * sign <= 0)
		return (-2);
	return ((int)(sign * num));
}
