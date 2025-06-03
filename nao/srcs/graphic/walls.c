#include "liball.h"
#include "raycasting.h"

void set_wall_x(t_ray *rays, t_all *all, t_player *player, float angle)
{
	float	wall_x;
	//int tex_x;

	if (rays->tex == &all->north || rays->tex == &all->south)
		wall_x = player->x + rays->dist * cos(angle);
	else
		wall_x = player->y + rays->dist * sin(angle);
	wall_x -= floor(wall_x);

// 	tex_x = (int)(wall_x * rays->tex->width);
// 	if (rays->tex == &all->south || rays->tex == &all->east)
// 		tex_x = rays->tex->width - tex_x - 1; // mirroring
}