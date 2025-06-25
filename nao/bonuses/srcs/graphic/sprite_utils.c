#include "liball.h"

int	count_sprites(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	sort_sprites_by_distance(t_sprite *sprites, int count)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (sprites[i].dist < sprites[j].dist)
			{
				tmp = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	get_sprite_tex_x(int s_screen_x, int s_size, int x, t_img *tex)
{
	int	relative_x;
	int	tex_x;

	relative_x = x - (s_screen_x - s_size / 2);
	tex_x = (relative_x * tex->width) / s_size;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}
