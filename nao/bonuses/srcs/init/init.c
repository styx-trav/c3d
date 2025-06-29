/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:44 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:45 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liball.h"
#include "libmap.h"
#include "libparsing.h"

static int	set_textures(t_all *all, t_pars *parse)
{
	if (!set_ns(all, parse))
		return (0);
	all->east.img = mlx_xpm_file_to_image(all->mlx, parse->east,
			&(all->east.width), &(all->east.height));
	if (!all->east.img)
	{
		free_parse(parse, "east texture");
		return (0);
	}
	all->west.img = mlx_xpm_file_to_image(all->mlx, parse->west,
			&(all->west.width), &(all->west.height));
	if (!all->west.img)
	{
		free_parse(parse, "west texture");
		return (0);
	}
	return (1);
}

static void	texture_addresses(t_all *all)
{
	img_address(&all->north);
	img_address(&all->south);
	img_address(&all->east);
	img_address(&all->west);
	img_address(&all->doors);
}

static int	mlx_setup(t_all *all, int width, int height)
{
	start_all(all);
	all->mlx = mlx_init();
	if (!all->mlx)
		return (0);
	all->win = mlx_new_window(all->mlx, width, height, "cube3d");
	if (!all->win)
		return (0);
	all->bg.img = mlx_new_image(all->mlx, width, height);
	if (!all->bg.img)
		return (0);
	all->fg.img = mlx_new_image(all->mlx, width, height);
	if (!all->fg.img)
		return (0);
	all->fg.width = width;
	all->fg.height = height;
	all->bg.width = width;
	all->bg.height = height;
	img_address(&all->fg);
	img_address(&all->bg);
	return (1);
}

void	init2(t_all *all, t_maps *map)
{
	all->player.y = (double)map->i;
	all->player.x = (double)map->j;
	all->dir = map->dir;
	all->map = map->map;
	free(map);
	all->sprite_count = count_sprites(all->map);
	if (!init_sprites(all))
		all->sprite.x = -1;
}

int	init(t_all *all, char *filename, int width, int height)
{
	t_pars	*parse;
	t_maps	*map;

	if (!mlx_setup(all, width, height))
		return (0);
	parse = parsing_pt1_el(filename);
	if (!parse)
		return (0);
	if (!set_textures(all, parse))
		return (0);
	texture_addresses(all);
	all->floor = calc_color(parse->floor);
	all->ceiling = calc_color(parse->ceiling);
	map = get_map(make_map(parse));
	free_parse(parse, NULL);
	if (!map)
		return (0);
	init2(all, map);
	if (!init_minimap(all))
	{
		printf("minimap init\n");
		return (0);
	}
	return (1);
}
