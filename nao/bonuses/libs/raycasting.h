/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:21:32 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:21:33 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "liball.h"

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
	int		door;
	t_img	*tex;
}	t_ray;

typedef struct s_render
{
	t_ray	*ray;
	int		x;
	int		tex_x;
	float	height;
	t_all	*all;
}	t_render;

//from graphic/walls.c
int		get_tex_x(t_ray *ray, t_player *player, float angle, t_all *all);
void	draw_column(t_render *r, int y);
void	set_dir_walls(t_ray *rays, t_all *all);

//from graphic/disp_utils.c
int		wall_dist_inloop(t_ray *r);

#endif
