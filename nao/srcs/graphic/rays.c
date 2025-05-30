#include "liball.h"

static void draw_one_ray(float angle, t_all *all, t_player *player)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	while(!touch(ray_x, ray_y, all))
	{
		put_pixel((int)ray_x, (int)ray_y, 0xFF0000, &all->fg);
		ray_x -= cos_angle;
		ray_y -= sin_angle;
	}
}

void    draw_rays(t_all *all, t_player *player)
{
	float fov;
	float start_angle;
	float angle;
	int i;

	fov = PI / 2;
	start_angle = player->angle - (fov / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		angle = start_angle + ((float)i / NUM_RAYS) * fov;
		draw_one_ray(angle, all, player);
		i++;
	}
}
