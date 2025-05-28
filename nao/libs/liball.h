#ifndef LIBALL_H
# define LIBALL_H

# define WIDTH 1280
# define HEIGHT 720

# define W 119
# define A 97
# define S 115
# define D 100

# define  PI 3.14159265359

# include <stdlib.h>
#include <stdbool.h>
# include <mlx.h>

typedef struct s_player
{
	double x;
	double y;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;
}	t_player;

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

// typedef struct s_mx
// {
// 	double	x;
// 	double	y;
// }		t_mx;

typedef struct s_all
{
	void	*mlx;
	void	*win;
	t_img	fg;
	t_img	bg;
	t_img	north;
	t_img	east;
	t_img	south;
	t_img	west;
	int		floor;
	int		ceiling;
	char	**map;
	t_player	player;
	char	dir;//angle ?? double, matrix ? add later;
}			t_all;

//from init/

//from init_utils.c
int	calc_color(int col[4]);
void	img_address(t_img *img);
void	start_all(t_all *all);

//from init.c
int	init(t_all *all, char *filename, int width, int height);

//from graphic
void draw_square(int x, int y, int size, int color, t_img *img);
void put_pixel(int x, int y, int color, t_img *img);
void init_player(t_player *player);
int key_press(int keycode, t_all *all);
int key_release(int keycode, t_all *all);
void move_player(t_player *player);
int draw_loop(t_all *all);

#endif
