/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:05:10 by acousini          #+#    #+#             */
/*   Updated: 2022/01/20 15:16:06 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	can_move(char **map, t_point next_move, int consomable_left)
{
	char	next_position;

	next_position = map[next_move.y][next_move.x];
	if (next_position == '0' || next_position == 'C'
		|| (next_position == 'E' && consomable_left == 0))
		return (0);
	return (1);
}

int	change_pos(t_root *root, t_point next_move)
{
	if (can_move(root->vars->map, next_move, root->vars->collected) == 1)
		return (1);
	if (root->vars->map[next_move.y][next_move.x] == 'E')
		clean_struct_root(root, "success");
	else if (root->vars->map[next_move.y][next_move.x] == 'C')
		root->vars->collected--;
	root->vars->map[next_move.y][next_move.x] = 'P';
	root->vars->map[root->vars->player.y][root->vars->player.x] = '0';
	ft_putstr_fd("\r                                                 ", 1);
	ft_putstr_fd("\rMove count: ", 1);
	ft_putnbr_fd(++root->vars->player_move, 1);
	return (0);
}

void	moves(t_root *root, int direction)
{
	t_point		player_pos;

	player_pos.x = root->vars->player.x;
	player_pos.y = root->vars->player.y;
	if (direction == KEY_UP)
		player_pos.y--;
	else if (direction == KEY_DOWN)
		player_pos.y++;
	else if (direction == KEY_LEFT)
		player_pos.x--;
	else if (direction == KEY_RIGHT)
		player_pos.x++;
	if (change_pos(root, player_pos) == 0)
	{
		root->vars->player.x = player_pos.x;
		root->vars->player.y = player_pos.y;
	}
}
