/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:39:23 by ylahssin          #+#    #+#             */
/*   Updated: 2024/10/25 13:50:01 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*s1;

	s1 = s;
	while (len > 0)
		s1[--len] = 0;
}
/*
#include <stdio.h>

int	main(void)
{
	char	arr[10];

			arr[10] = "mikemok";
	ft_bzero(arr, sizeof(arr));
	for (int i = 0; i < 10; i++)
		printf("%d", arr[i]);
	return (0);
}
*/
