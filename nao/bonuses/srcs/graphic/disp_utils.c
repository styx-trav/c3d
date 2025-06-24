#include "liball.h"
#include "raycasting.h"

void	put_pixel(int x, int y, int color, t_img *img)
{
	int	index;

	if (!img || !img->addr || x < 0 || y < 0
		|| x >= img->width || y >= img->height)
		return ;
	index = y * img->size_line + x * img->bpp / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

int	is_wall(t_all *all, float x, float y)
{
	int	check_x;
	int	check_y;

	check_x = (int)x;
	check_y = (int)y;
	if (check_y < 0 || check_x < 0 || !all->map[check_y]
		|| check_x >= (int)ft_strlen(all->map[check_y])
		|| all->map[check_y][check_x] == '\0'
		|| all->map[check_y][check_x] == '1'
		|| all->map[check_y][check_x] == ' '
		|| all->map[check_y][check_x] == '?')
		return (1);
	return (0);
}

int	collision_zone(t_all *all, float px, float py)
{
	float	zone;
	float	dy;
	float	dx;

	zone = 0.05f;
	dy = -zone;
	while (dy <= zone)
	{
		dx = -zone;
		while (dx <= zone)
		{
			if (is_wall(all, px + dx, py + dy))
				return (1);
			dx += zone;
		}
		dy += zone;
	}
	return (0);
}

int	wall_dist_inloop(t_ray *r)
{
	int	side;

	if (r->distx > r->disty)
	{
		side = 1;
		r->disty = r->disty + r->deltay;
		r->mapy += r->stepy;
	}
	else
	{
		side = 0;
		r->distx = r->distx + r->deltax;
		r->mapx += r->stepx;
	}
	return (side);
}
