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
}	t_ray;

//void    raycast(t_all *all);
//void    draw_wall_column(t_all *all, int x, int height, t_img *texture);

#endif
