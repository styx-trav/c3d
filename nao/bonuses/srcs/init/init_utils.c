/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:46 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:47 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liball.h"

int	calc_color(int col[4])
{
	unsigned char	color[4];

	color[0] = (unsigned char)(col[3]);
	color[1] = (unsigned char)(col[2]);
	color[2] = (unsigned char)(col[1]);
	color[3] = 0;
	return ((*(int *)color));
}

void	img_address(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian);
}

void	start_all(t_all *all)
{
	all->mlx = NULL;
	all->win = NULL;
	all->bg.img = NULL;
	all->fg.img = NULL;
	all->north.img = NULL;
	all->east.img = NULL;
	all->south.img = NULL;
	all->west.img = NULL;
	all->doors.img = NULL;
	all->map = NULL;
	all->sprites = NULL;
	all->sprite_count = 0;
}

unsigned long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}

int	set_ns(t_all *all, t_pars *parse)
{
	all->doors.img = mlx_xpm_file_to_image(all->mlx, "./textures/door.xpm",
			&(all->doors.width), &(all->doors.height));
	if (!all->doors.img)
	{
		free_parse(parse, "doors texture");
		return (0);
	}
	all->north.img = mlx_xpm_file_to_image(all->mlx, parse->north,
			&(all->north.width), &(all->north.height));
	if (!all->north.img)
	{
		free_parse(parse, "north texture");
		return (0);
	}
	all->south.img = mlx_xpm_file_to_image(all->mlx, parse->south,
			&(all->south.width), &(all->south.height));
	if (!all->south.img)
	{
		free_parse(parse, "south texture");
		return (0);
	}
	return (1);
}
