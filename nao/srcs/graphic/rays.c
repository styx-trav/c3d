#include "liball.h"

static void add_deltas(float angle, t_all *all, t_player *player, int i)
{
	float cos_angle = cos(angle);
	float sin_angle = sin(angle);
	float ray_x = player->x;// / 64;
	float ray_y = player->y;// / 64;
	float deltax = fabs(1/cos_angle);
	float deltay = fabs(1/sin_angle);
	int wall = 0;
	int side = 0;
	float distx = 0;
	float disty = 0;
	float dist = 0;
	int mapx = (int) (ray_x);
	int mapy = (int) (ray_y);
	float height;
	int start_y;
	int end;

	if (cos_angle > 0)
		distx = (ray_x - (float)mapx) * deltax;
	else
		distx = ((float)mapx + 1.0 - ray_x) * deltax;
	if (sin_angle > 0)
		disty = (ray_y - (float)mapy) * deltay;
	else
		disty = ((float)mapy + 1.0 - ray_y) * deltay;
	while (!wall)
	{
		if (distx > disty)
		{
			side = 1;
			disty = disty + deltay;
			if (sin_angle > 0)
				mapy--;
			else
				mapy++;
		}
		else
		{
			side = 0;
			distx = distx + deltax;
			if (cos_angle > 0)
				mapx--;
			else
				mapx++;
		}
		if (all->map[mapy][mapx] == ' ' || all->map[mapy][mapx] == '1')
			wall = 1;
	}
	if (side)
		dist = (disty - deltay);// * 64;
	else
		dist = (distx - deltax);// * 64;
	// ray_x = player->x - (cos_angle * dist);
	// ray_y = player->y - (sin_angle * dist);
	// put_pixel(ray_x, ray_y, 0x0000FF, &all->fg);

	dist *= cos(angle - player->angle);//fish-eye effect
	height = (1 / dist) * (WIDTH / 2); // 64 instead of one
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 255, &all->fg);
		start_y++;
	}
}

void draw_one_ray(float angle, t_all *all, t_player *player)
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
		//draw_one_ray(angle, all, player, i);
		add_deltas(angle, all, player, i);
		i++;
	}
}
