/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:33:14 by ylahssin          #+#    #+#             */
/*   Updated: 2024/10/25 18:54:55 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	total_len;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		result = (char *)(malloc(sizeof(char)));
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	total_len = ft_strlen((char *)(s + start));
	if (total_len > len)
		total_len = len;
	result = (char *)(malloc(sizeof(char) * (total_len + 1)));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)(s + start), total_len + 1);
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;

	str = "yassin lahssini",*strsub;
    if (!(strsub = ft_substr(str, 0, 10)))
        printf("NULL");
    else
        printf( "%s\n", strsub);
    if (str == strsub)
        printf("\nA new string was not returned");
}
*/
