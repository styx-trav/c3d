/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:24:48 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/11 19:24:50 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	add_deltas(float angle, t_all *all, t_player *player, int i)
{
	t_ray		ray;
	t_render	render;

	ray.deltax = fabs(1 / cos(angle));
	ray.deltay = fabs(1 / sin(angle));
	rays_set_up(&ray, angle, &all->player);
	set_dir_walls(&ray, all);
	ray.dist *= cos(angle - all->player.angle);
	render.ray = &ray;
	render.x = i;
	render.height = (1 / ray.dist) * (WIDTH / 2);
	render.tex_x = get_tex_x(&ray, player, angle, all);
	render.all = all;
	draw_column(&render);
}

void	draw_rays(t_all *all, t_player *player)
{
	float	fov;
	float	start_angle;
	float	angle;
	int		i;

	fov = PI / 2.5;
	start_angle = player->angle - (fov / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		angle = start_angle + ((float)i / NUM_RAYS) * fov;
		add_deltas(angle, all, player, i);
		i++;
	}
}
