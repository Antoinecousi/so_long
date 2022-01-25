/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_structs_first.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:44:27 by acousini          #+#    #+#             */
/*   Updated: 2022/01/20 14:34:51 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_root_and_file(t_root *root, char *file, char *error)
{
	free(file);
	clean_struct_root(root, error);
}

void	clean_vars(t_vars *vars)
{
	int		i;

	i = 0;
	if (vars != 0)
	{
		if (vars->map != 0)
		{
			while (vars->map[i])
				free(vars->map[i++]);
			free(vars->map);
		}
		free(vars);
	}
}

void	clean_struct_texture(void *mlx, t_text *texture)
{
	if (texture)
		mlx_destroy_image(mlx, texture);
}

void	clean_mlx(void *mlx)
{
	mlx_destroy_display(mlx);
	mlx_loop_end(mlx);
	free(mlx);
}

void	clean_struct_root(t_root *root, char *msg)
{
	if (root != 0)
	{
		clean_struct_texture(root->mlx, root->blank);
		clean_struct_texture(root->mlx, root->wall);
		clean_struct_texture(root->mlx, root->player);
		clean_struct_texture(root->mlx, root->exit);
		clean_struct_texture(root->mlx, root->consumable);
		if (root->win != 0)
			mlx_destroy_window(root->mlx, root->win);
		if (root->mlx != 0)
			clean_mlx(root->mlx);
		if (root->vars != 0)
			clean_vars(root->vars);
	}
	if (ft_strncmp(msg, "success", 7))
	{
		write(1, "Error\n", 7);
		ft_putstr_fd(msg, 2);
	}
	exit(0);
}
