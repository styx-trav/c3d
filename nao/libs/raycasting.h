#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "liball.h"
#include <math.h>

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}	t_ray;

void    raycast(t_all *all);
void    draw_wall_column(t_all *all, int x, int height, t_img *texture);

#endif