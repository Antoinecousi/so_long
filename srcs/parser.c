/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 19:29:23 by acousini          #+#    #+#             */
/*   Updated: 2022/01/23 18:38:38 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_error_map(int nb_err)
{
	if (nb_err == MAP_NOT_CLOSED)
		return ("MAP ISN'T CLOSED PROPERLY\n");
	if (nb_err == COLLECTIBLE)
		return ("WRONG COLLECTIBLE NUMBER\n");
	if (nb_err == PLAYER)
		return ("WRONG PLAYER NUMBER\n");
	if (nb_err == EXIT)
		return ("WRONG EXIT NUMBER\n");
	if (nb_err == RECTANGLE)
		return ("MAP ISN'T A RECTANGLE\n");
	if (nb_err == WRONG_CHAR)
		return ("UNRECOGNIZED CHARACTER IN MAP\n");
	return ("ERROR WITH MAP\n");
}

void	init_t_map(t_map *max)
{
	max->i = 0;
	max->j = 0;
	max->reader_e = 0;
	max->reader_p = 0;
	max->reader_c = 0;
}

void	is_map_rectangle(char **map, t_map *max, t_root *root)
{
	int		readerx;
	int		x;
	int		y;

	x = 0;
	y = 0;
	readerx = 0;
	while (map[y])
	{
		while (map[y][x])
			x++;
		if (y == 0)
			readerx = x;
		if (readerx != x)
			clean_struct_root(root, ft_error_map(RECTANGLE));
		y++;
		x = 0;
	}
	if (readerx <= 2 || y <= 2)
		clean_struct_root(root, ft_error_map(RECTANGLE));
	max->i = y - 1;
	max->j = readerx - 1;
	root->vars->width = max->j + 1;
	root->vars->height = max->i + 1;
}

void	parse_map_second(char *map, t_map *max, t_root *root, int j)
{
	if (!ft_strchr("PCE10", map[j]))
		clean_struct_root(root, ft_error_map(WRONG_CHAR));
	max->reader_p += map[j] == 'P';
	max->reader_c += map[j] == 'C';
	max->reader_e += map[j] == 'E';
	if (map[j] == 'P')
		root->vars->player.x = j;
}

void	parse_map(char **map, t_map max, t_root *root)
{
	int		i;
	int		j;

	is_map_rectangle(map, &max, root);
	i = -1;
	while (++i <= max.i)
	{
		j = -1;
		while (map[i][++j])
		{
			parse_map_second(map[i], &max, root, j);
			if ((i == 0 || i == max.i || j == 0
					|| j == max.j) && map[i][j] != '1')
				clean_struct_root(root, ft_error_map(MAP_NOT_CLOSED));
			if (map[i][j] == 'P')
				root->vars->player.y = i;
		}
	}
	if (max.reader_c < 1)
		clean_struct_root(root, ft_error_map(COLLECTIBLE));
	if (max.reader_p != 1)
		clean_struct_root(root, ft_error_map(PLAYER));
	if (max.reader_e < 1)
		clean_struct_root(root, ft_error_map(EXIT));
	root->vars->collected = max.reader_c;
}
