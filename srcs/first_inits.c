/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:01:23 by acousini          #+#    #+#             */
/*   Updated: 2022/01/23 19:12:01 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win_hook(t_root *root)
{
	clean_struct_root(root, "success");
	return (1);
}

int	key_press_hook(int keycode, t_root *root)
{
	if (keycode != KEY_DOWN || keycode != KEY_RIGHT
		|| keycode != KEY_LEFT || keycode != KEY_UP)
	{
		moves(root, keycode);
		draw_map(root, -1, -1);
	}
	if (keycode == 65307)
		close_win_hook(root);
	return (0);
}

int	load_textures(t_root *root)
{
	int		img_width;
	int		img_height;

	root->player = mlx_xpm_file_to_image(root->mlx,
			"xpm/player.xpm", &img_width, &img_height);
	if (root->player == NULL)
		return (1);
	root->wall = mlx_xpm_file_to_image(root->mlx,
			"xpm/wall.xpm", &img_width, &img_height);
	if (root->wall == NULL)
		return (1);
	root->exit = mlx_xpm_file_to_image(root->mlx,
			"xpm/exit.xpm", &img_width, &img_height);
	if (root->exit == NULL)
		return (1);
	root->consumable = mlx_xpm_file_to_image(root->mlx,
			"xpm/consumable.xpm", &img_width, &img_height);
	if (root->consumable == NULL)
		return (1);
	root->blank = mlx_xpm_file_to_image(root->mlx,
			"xpm/blank.xpm", &img_width, &img_height);
	if (root->blank == NULL)
		return (1);
	return (0);
}

void	initialise_t_vars(t_root *root, char *path)
{
	root->vars = (t_vars *)malloc(sizeof(t_vars));
	if (root->vars == 0)
		clean_struct_root(root,
			"problem with malloc in initialise_t_vars. Abort.");
	root->vars->map = 0;
	root->vars->player_move = 0;
	ber_to_map(root, path);
}

void	initialise_t_root(char *map)
{
	t_root	root;

	root.mlx = NULL;
	root.win = NULL;
	root.blank = NULL;
	root.player = NULL;
	root.consumable = NULL;
	root.wall = NULL;
	root.exit = NULL;
	initialise_t_vars(&root, map);
	root.mlx = mlx_init();
	if (root.mlx == NULL)
		clean_struct_root(&root, "mlx not launched. Abort.");
	root.win = mlx_new_window(root.mlx,
			root.vars->width * DIM, root.vars->height * DIM, "so_long");
	if (root.win == NULL)
		clean_struct_root(&root, "win not launched. Abort.");
	if (load_textures(&root))
		clean_struct_root(&root, "problem with textures");
	draw_map(&root, -1, -1);
	mlx_key_hook(root.win, key_press_hook, &root);
	mlx_hook(root.win, 17, 1L << 17, close_win_hook, &root);
	mlx_loop(root.mlx);
	mlx_loop_hook(root.mlx, draw_map, &root);
}
