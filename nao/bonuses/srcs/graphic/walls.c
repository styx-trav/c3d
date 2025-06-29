/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:49 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:50 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ray->door)
		ray->tex = &all->doors;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * ray->tex->width);
	return (tex_x);
}

void	draw_column(t_render *r, int y)
{
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
		if (y > r->all->minimap_h || r->x > r->all->minimap_w)
			put_pixel(r->x, y, *(unsigned int *)px, &r->all->fg);
		y++;
	}
}

static int	wall_dist(t_ray *r, char **map, bool see)
{
	int	wall;
	int	side;

	wall = 0;
	side = 0;
	while (!wall)
	{
		side = wall_dist_inloop(r);
		if (map[r->mapy][r->mapx] == ' ' || map[r->mapy][r->mapx] == '1'
			|| map[r->mapy][r->mapx] == '?'
			|| (see && map[r->mapy][r->mapx] == '*'))
			wall = 1;
		if (map[r->mapy][r->mapx] == '?')
			side += 2;
	}
	return (side);
}

static int	set_up_dir(t_ray *rays, t_all *all)
{
	int	res;

	rays->color = 0x00F000;
	rays->tex = NULL;
	res = wall_dist(rays, all->map, all->see_3);
	rays->door = 0;
	if (res > 1)
	{
		rays->door = 1;
		res -= 2;
	}
	return (res);
}

void	set_dir_walls(t_ray *rays, t_all *all)
{
	int	res;

	res = set_up_dir(rays, all);
	if (res)
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
