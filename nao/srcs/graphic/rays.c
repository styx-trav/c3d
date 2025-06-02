#include "liball.h"
#include "raycasting.h"

static void	rays_set_up(t_ray *rays, float angle, t_player *player)
{
	int	mapx;
	int	mapy;

	mapx = (int)player->x;
	mapy = (int)player->y;
	rays->stepx = 1;
	rays->stepy = 1;
	if (cos(angle) > 0)
		rays->stepx = -1;
	if (sin(angle) > 0)
		rays->stepy = -1;
	if (rays->stepx < 0)
		rays->distx = (player->x - (float)mapx) * rays->deltax;
	else
		rays->distx = ((float)mapx + 1.0 - player->x) * rays->deltax;
	if (rays->stepy < 0)
		rays->disty = (player->y - (float)mapy) * rays->deltay;
	else
		rays->disty = ((float)mapy + 1.0 - player->y) * rays->deltay;
	rays->mapx = mapx;
	rays->mapy = mapy;
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
		if (map[r->mapy][r->mapx] == ' ' || map[r->mapy][r->mapx] == '1')
			wall = 1;
	}
	return (side);
}

static void	add_deltas(float angle, t_all *all, t_player *player, int i)
{
	t_ray	rays;
	float	height;
	int		start_y;
	int		end;

	rays.deltax = fabs(1 / cos(angle));
	rays.deltay = fabs(1 / sin(angle));
	rays_set_up(&rays, angle, player);
	rays.color = 0x00F000;
	if (wall_dist(&rays, all->map))
	{
		rays.dist = rays.disty - rays.deltay;
		rays.color = 0x0000F0;
	}
	else
		rays.dist = rays.distx - rays.deltax;
	rays.dist *= cos(angle - player->angle);
	height = (1 / rays.dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, rays.color, &all->fg);
		start_y++;
	}
}

void	draw_rays(t_all *all, t_player *player)
{
	float	fov;
	float	start_angle;
	float	angle;
	int		i;

	fov = PI / 2;
	start_angle = player->angle - (fov / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		angle = start_angle + ((float)i / NUM_RAYS) * fov;
		add_deltas(angle, all, player, i);
		i++;
	}
}
