/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:02:01 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/11 21:02:02 by naorakot         ###   ########.fr       */
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

//from walls.c
int		get_tex_x(t_ray *ray, t_player *player, float angle, t_all *all);
void	draw_column(t_render *r);
void	set_dir_walls(t_ray *rays, t_all *all);

#endif
