/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:34:45 by acousini          #+#    #+#             */
/*   Updated: 2022/01/23 19:12:19 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(char *map)
{
	int		size;

	size = ft_strlen(map);
	if (ft_strncmp(map + size - 4, ".ber", 4) != 0)
		return (ERROR);
	if (map == ERROR)
		return (ERROR);
	if (size < 5)
		return (ERROR);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || check_ber(argv[1]) == 0)
	{
		write(1, "usage: ./so_long [map.ber]", 27);
		return (0);
	}
	initialise_t_root(argv[1]);
}
