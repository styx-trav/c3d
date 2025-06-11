#include "liball.h"
#include "raycasting.h"

int	get_tex_x(t_ray *ray, t_player *player, float angle, t_all *all)
{
	float	wall_x;
	int		tex_x;

	if (ray->tex == &all->north || ray->tex == &all->south)
		wall_x = player->x + ray->dist * -cos(angle);
	else
		wall_x = player->y + ray->dist * -sin(angle);
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * ray->tex->width);
	return (tex_x);
}

void	draw_column(t_render *r)
{
	int				y;
	int				d;
	int				end;
	int				tex_y;
	char			*px;

	y = (HEIGHT - r->height) / 2;
	end = y + r->height;
	while (y < end)
	{
		d = y * 256 - HEIGHT * 128 + r->height * 128;
		tex_y = (d * r->ray->tex->height) / ((int)r->height * 256);
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= r->ray->tex->height)
			tex_y = r->ray->tex->height - 1;
		px = r->ray->tex->addr + (tex_y * r->ray->tex->size_line
				+ r->tex_x * (r->ray->tex->bpp / 8));
		put_pixel(r->x, y, *(unsigned int *)px, &r->all->fg);
		y++;
	}
}

static int	wall_dist(t_ray *r, char **map)
{
	int	wall;
	int	side;

	wall = 0;
	side = 0;
	while (!wall)
	{
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
		if (map[r->mapy][r->mapx] == ' ' || map[r->mapy][r->mapx] == '1'
			|| map[r->mapy][r->mapx] == '?')// || map[r->mapy][r->mapx] == '3')
			wall = 1;
	}
	return (side);
}

void	set_dir_walls(t_ray *rays, t_all *all)
{
	rays->color = 0x00F000;
	if (wall_dist(rays, all->map))
	{
		rays->dist = rays->disty - rays->deltay;
		if (rays->stepy < 0)
			rays->tex = &all->north;
		else
			rays->tex = &all->south;
	}
	else
	{
		rays->dist = rays->distx - rays->deltax;
		if (rays->stepx < 0)
			rays->tex = &all->west;
		else
			rays->tex = &all->east;
	}
}
