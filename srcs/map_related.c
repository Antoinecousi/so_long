/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:01:08 by acousini          #+#    #+#             */
/*   Updated: 2022/01/23 19:15:40 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	double_newline(char *file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '\n')
		{
			i++;
			if (file[i] == '\n')
				return (1);
		}
		if (file[i])
			i++;
	}
	return (0);
}

char	*ft_strjoin_doublefree(char *s1, char *s2, int i, int j)
{
	char	*new;
	int		size;

	size = 0;
	size = ft_strlen(s1);
	if (!s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s2) + size + 1));
	if (!new)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
	}
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	if (s1)
		free(s1);
	return (new);
}

char	*read_file(t_root *root, char buf[], int fd, char *file)
{
	int				reader;

	reader = 1;
	while (reader != 0)
	{
		reader = read(fd, buf, 512);
		if (reader == -1)
		{
			free(file);
			close(fd);
			clean_struct_root(root, "problem with read in read_file. Abort.");
		}
		else
		{
			buf[reader] = '\0';
			file = ft_strjoin_doublefree(file, buf, 0, -1);
			if (file == NULL)
			{
				close(fd);
				clean_struct_root(root,
					"problem with malloc in read_file. Abort.");
			}
		}
	}
	return (file);
}

void	ber_to_map(t_root *root, char *path)
{
	char	*file;
	int		fd;
	char	buf[513];
	t_map	max;

	fd = open(path, O_RDONLY | O_NOFOLLOW);
	if (fd == -1)
		clean_struct_root(root, "problem with open in ber_to_map. Abort.");
	file = malloc(1);
	if (!file)
		clean_root_and_file(root, file,
			"problem with malloc in ber_to_map. Abort.");
	*file = '\0';
	file = read_file(root, buf, fd, file);
	close(fd);
	if (double_newline(file))
		clean_root_and_file(root, file, "map have an empty newline. Abort.");
	root->vars->map = ft_split_backn(root, file, '\n');
	init_t_map(&max);
	free(file);
	parse_map(root->vars->map, max, root);
}

int	draw_map(t_root *root, int i, int j)
{
	while (root->vars->map[++i])
	{
		j = -1;
		while (root->vars->map[i][++j])
		{
			if (root->vars->map[i][j] == '1')
				mlx_put_image_to_window(root->mlx,
					root->win, root->wall, j * DIM, i * DIM);
			else if (root->vars->map[i][j] == 'P')
				mlx_put_image_to_window(root->mlx,
					root->win, root->player, j * DIM, i * DIM);
			else if (root->vars->map[i][j] == 'C')
				mlx_put_image_to_window(root->mlx,
					root->win, root->consumable, j * DIM, i * DIM);
			else if (root->vars->map[i][j] == 'E')
				mlx_put_image_to_window(root->mlx,
					root->win, root->exit, j * DIM, i * DIM);
			else if (root->vars->map[i][j] == '0')
				mlx_put_image_to_window(root->mlx,
					root->win, root->blank, j * DIM, i * DIM);
		}
	}
	return (0);
}
