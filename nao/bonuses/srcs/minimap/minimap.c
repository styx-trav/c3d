#include "liball.h"

int	init_minimap(t_all *all)
{
	int	height;
	int	width;

	height = 0;
	while (all->map[height])
		height++;
	width = 0;
	while (all->map[0][width])
		width++;
	all->minimap_w = width * 10;
	all->minimap_h = height * 10;
	return (1);
}

static int	minimap_setup(char **map, int *j)
{
	int	i;

	i = 0;
	while (map[i])
	{
		*j = 0;
		while (map[i][*j])
		{
			if (map[i][*j] == '*')
				return (i);
			*j = *j +1;
		}
		i++;
	}
	return (-1);
}

static void	draw_square(t_all *all, int y, int x, int color)
{
	int	size;
	int	i;
	int	j;

	size = 10;
	if (color != 0x00FFFFFF)
		size = 2;
	i = 0;
	if (size == 2)
		i = -2;
	while (i < size)
	{
		j = 0;
		if (size == 2)
			j = -2;
		while (j < size)
		{
			put_pixel(x + j, y + i, color, &all->fg);
			j++;
		}
		i++;
	}
}

static void	minimap(t_all *all, int on, int i, int j)
{
	int	is;
	int	js;

	is = 0;
	while (all->map[is])
	{
		js = 0;
		while (all->map[is][js])
		{
			if (!on && js > j && i != -1)
			{
				if (!(is > 1 && is >= i -1 && is <= i +1)
					&& all->map[is][js] == 1)
					draw_square(all, is * 10, js * 10, 0x00FFFFFF);
			}
			else if (all->map[is][js] == '1')
				draw_square(all, is * 10, js * 10, 0x00FFFFFF);
			else if (all->map[is][js] == 'S')
				draw_square(all, is * 10, js * 10, 0x000000FF);
			js++;
		}
		is++;
	}
}

void	draw_minimap(t_all *all, t_player *player)
{
	static int	lswitch = 0;
	int			i;
	int			j;

	if (!lswitch && !all->see_3)
		lswitch++;
	j = 0;
	i = minimap_setup(all->map, &j);
	minimap(all, lswitch, i, j);
	draw_square(all, (int)(player->y * 10), (int)(player->x * 10), 0x00FF0000);
	player_arrow(&all->fg, (int)(player->x * 10),
		(int)(player->y * 10), player->angle);
}
