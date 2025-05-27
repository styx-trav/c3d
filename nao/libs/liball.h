#ifndef LIBALL_H
# define LIBALL_H

# include <stdlib.h>
# include <mlx.h>

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}		t_img;

typedef struct s_mx
{
	double	x;
	double	y;
}		t_mx;

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
	t_mx	player;
	char	dir;//angle ?? double, matrix ? add later;
}			t_all;

//from init/

//from init_utils.c
int	calc_color(int col[4]);
void	img_address(t_img *img);
void	start_all(t_all *all);

//from init.c
int	init(t_all *all, char *filename, int width, int height);

#endif
