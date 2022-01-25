/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:34:43 by acousini          #+#    #+#             */
/*   Updated: 2022/01/23 19:28:18 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>

# define DIM				32
# define KEY_DOWN			115
# define KEY_UP				119
# define KEY_LEFT			97
# define KEY_RIGHT			100
# define MAP_NOT_CLOSED		101
# define COLLECTIBLE		102
# define PLAYER				103
# define EXIT				104
# define RECTANGLE			105
# define WRONG_CHAR			106
# define SUCCESS			1
# define ERROR				0

typedef struct s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct s_text
{
	void	*img;
	char	*addr;
	int		init;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_text;

typedef struct s_vars
{
	char			**map;
	int				height;
	int				width;
	int				colls;
	int				collected;
	int				player_move;
	t_point			player;
}				t_vars;

typedef struct s_root
{
	void	*mlx;
	void	*win;
	t_text	*player;
	t_text	*consumable;
	t_text	*exit;
	t_text	*blank;
	t_text	*wall;
	t_vars	*vars;
}				t_root;

typedef struct s_map
{
	int		i;
	int		j;
	int		reader_e;
	int		reader_p;
	int		reader_c;
}				t_map;

// clean & exits
void	clean_root_and_file(t_root *root, char *file, char *error);
void	clean_struct_root(t_root *root, char *msg);
int		ft_error(int nb_err);

// initialize
void	init_t_map(t_map *max);
void	initialise_t_root(char *map);
void	initialise_hooks(t_root *root);
void	init_t_map(t_map *max);

// moves
void	moves(t_root *root, int direction);
int		key_press_hook(int keycode, t_root *root);

//map related
int		load_textures(t_root *root);
void	ber_to_map(t_root *root, char *path);
int		draw_map(t_root *root, int i, int j);
void	parse_map(char **map, t_map max, t_root *root);
void	is_map_rectangle(char **map, t_map *max, t_root *root);
int		check_ber(char *map);

// miscellaneous
char	**ft_split_backn(t_root *root, char *s, char c);
int		double_newline(char *file);
int		close_win_hook(t_root *root);

#endif
