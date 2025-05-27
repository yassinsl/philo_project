/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:53:11 by ylahssin          #+#    #+#             */
/*   Updated: 2025/05/26 18:46:05 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	main(int ac, char *av[])
{
	t_data_philosophers	philos_data;

	memset(&philos_data, 0, sizeof(t_data_philosophers));
	if (ac != 5 && ac != 6)
		return (ft_error_msg(INVALID_NUMBER), 1);
	if (get_data_from_args(&philos_data, av) == -1)
		return (1);
	if (create_mutexes(&philos_data) == -1)
		return (1);
	create_philosophers(&philos_data);
	create_threads(&philos_data);
	return (0);
}
