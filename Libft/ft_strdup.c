/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:39:28 by ylahssin          #+#    #+#             */
/*   Updated: 2024/10/25 12:49:30 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	char	*ptr;

	result = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	ptr = result;
	if (!result)
		return (NULL);
	while (*s)
		*ptr++ = *s++;
	*ptr = '\0';
	return (result);
}
