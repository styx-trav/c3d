#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct s_ray
{
	int		mapx;
	int		mapy;
	double	dist;
	double	distx;
	double	disty;
	double	deltax;
	double	deltay;
	int		stepx;
	int		stepy;
	int		color;
	t_img *tex;
}	t_ray;


//from walls.c
void set_wall_x(t_ray *rays, t_all *all, t_player *player, float angle);

#endif
