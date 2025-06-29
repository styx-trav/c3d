/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liball.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:01:29 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/17 13:22:04 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBALL_H
# define LIBALL_H

# define WIDTH 1280
# define HEIGHT 720

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define NUM_RAYS WIDTH

# define PI 3.14159265359

# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include <math.h>

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}		t_img;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_img		fg;
	t_img		bg;
	t_img		north;
	t_img		east;
	t_img		south;
	t_img		west;
	int			floor;
	int			ceiling;
	char		**map;
	t_player	player;
	char		dir;
}			t_all;

//from init/

//from init_utils.c
int		calc_color(int col[4]);
void	img_address(t_img *img);
void	start_all(t_all *all);

//from init.c
int		init(t_all *all, char *filename, int width, int height);

//from graphic

//from hooks.c
int		key_press(int keycode, t_all *all);
int		key_release(int keycode, t_all *all);
int		mouse_move(int x, int y, t_all *all);
int		exitt(t_all *str);

//from player.c
void	init_player(t_all *all, t_player *player);
void	rotate_player(t_player *player);
void	move_player(t_all *all, t_player *player);

//from disp_utils.c
void	put_pixel(int x, int y, int color, t_img *img);
int		collision_zone(t_all *all, float px, float py);

//from draw.c
int		draw_loop(t_all *all);

//from rays.c
void	draw_rays(t_all *all, t_player *player);

//from utils.c
size_t	ft_strlen(const char *s);
void	free_map(char **map);

#endif
