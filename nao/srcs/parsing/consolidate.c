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

int	set_textures(t_all *all, t_pars *parse)
{
	all->north.img = mlx_xpm_file_to_image(mlx.mlx, parse->north, &(all->north.width), &(all->north.height));
	if (!all->north.img)
	{
		free_parse(parse, "north texture");
		return (0);
	}
	all->south.img = mlx_xpm_file_to_image(mlx.mlx, parse->south, &(all->south.width), &(all->south.height));
	if (!all->south.img)
	{
		free_parse(parse, "south texture");
		return (0);
	}
	all->east.img = mlx_xpm_file_to_image(mlx.mlx, parse->east, &(all->east.width), &(all->east.height));
	if (!all->east.img)
	{
		free_parse(parse, "east texture");
		return (0);
	}
	all->west.img = mlx_xpm_file_to_image(mlx.mlx, parse->west, &(all->west.width), &(all->west.height));
	if (!all->west.img)
	{
		free_parse(parse, "west texture");
		return (0);
	}
	return (1);
}

void	img_address(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
}

void	texture_addresses(t_all *all)
{
	img_address(&all->north);
	img_address(&all->south);
	img_address(&all->east);
	img_address(&all->west);
}

int	mlx_setup(t_all *all, int width, int height)
{
	all->mlx = mlx_init();
	if (!all->mlx)
		return (0);
	all->win = mlx_new_window(all->mlx, width, height, "cube3d");
	if (!all->win)
		return (0);
	all->bg = mlx_new_image(all->mlx, width, height);
	if (!all->bg)
		return (0);
	all->fg = mlx_new_image(all->mlx, width, height);
	if (!all->fg)
		return (0);
	img_address(&all->fg);
	img_address(&all->bg);
	return (1);
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
	map = get_map(parse->map);
	free_parse(parse, NULL);
	if (!map)
		return (0);
	all->player.x = (double)map->i;
	all->player.y = (double)map->j;
	all->dir = map->dir;
	all->map = map->map;
	free(map);
	return (1);
}
