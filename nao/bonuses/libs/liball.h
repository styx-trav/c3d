/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liball.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:21:25 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:21:50 by ltantin          ###   ########.fr       */
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
# define SPRITE_FRAMES 3

# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include "libparsing.h"

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		tex_x;
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

typedef struct s_sprite
{
	t_img			img[SPRITE_FRAMES];
	int				frame_index;
	unsigned long	last_update;
	double			x;
	double			y;
	double			dist;
	int				screen_x;
	int				size;
}	t_sprite;

typedef struct s_door
{
	int		i;
	int		j;
	bool	seen;
}	t_door;

typedef struct s_assist
{
	int	x;
	int	y;
	int	istep;
	int	jstep;
}			t_assist;

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
	t_img		doors;
	int			minimap_w;
	int			minimap_h;
	int			floor;
	int			ceiling;
	char		**map;
	t_player	player;
	t_sprite	sprite;
	t_sprite	*sprites;
	int			sprite_count;
	float		z_buffer[WIDTH];
	char		dir;
	t_door		door;
	bool		see_3;
}			t_all;

//from init/init_utils.c
int				calc_color(int col[4]);
void			img_address(t_img *img);
void			start_all(t_all *all);
unsigned long	get_current_time_ms(void);
int				set_ns(t_all *all, t_pars *parse);

//from init/init.c
int				init(t_all *all, char *filename, int width, int height);

//from graphic/hooks.c
int				key_press(int keycode, t_all *all);
int				key_release(int keycode, t_all *all);
int				mouse_move(int x, int y, t_all *all);
int				open_door(int button, int x, int y, t_all *all);
int				exitt(t_all *str);

//from graphic/player.c
void			init_player(t_all *all, t_player *player);
void			rotate_player(t_player *player);
void			move_player(t_all *all, t_player *player);

//from graphic/disp_utils.c
void			put_pixel(int x, int y, int color, t_img *img);
int				collision_zone(t_all *all, float px, float py);

//from graphic/draw.c
int				draw_loop(t_all *all);

//from graphic/rays.c
void			draw_rays(t_all *all, t_player *player);

//from graphic/sprite.c
int				load_sprite_frames(t_sprite *sprite, void *mlx);
void			update_sprite(t_sprite *sprite);
int				init_sprites(t_all *all);

//from graphic/sprite_utils.c
int				count_sprites(char **map);
void			sort_sprites_by_distance(t_sprite *sprites, int count);
int				get_sprite_tex_x(int s_screen_x, int s_size, int x, t_img *tex);

//from graphic/draw_sprite.c
void			draw_all_sprites(t_all *all, t_player *player);

//from minimap/

//from minimap.c
int				init_minimap(t_all *all);
void			draw_minimap(t_all *all, t_player *player);

//from player_arrow.c
void			player_arrow(t_img *fg, int x, int y, float angle);

//from utils.c
size_t			ft_strlen(const char *s);
void			free_map(char **map);

#endif
