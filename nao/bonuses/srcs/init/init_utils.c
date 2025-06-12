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
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->endian);
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
	all->map = NULL;
}

unsigned long get_current_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000UL + tv.tv_usec / 1000UL);
}

#include <stdio.h>

int load_sprite_frames(t_sprite *sprite, void *mlx)
{
	int w;
	int h;
	int i = 0;

	sprite->frame_index = 0;
	sprite->last_update = get_current_time_ms();
	sprite->img[0] = mlx_xpm_file_to_image(mlx, "bonuses/tex_sprites/shrek_wazowski_eyesclosed.xpm", &w, &h);
	sprite->img[1] = mlx_xpm_file_to_image(mlx, "bonuses/tex_sprites/shrek_wazowski.xpm", &w, &h);
	sprite->img[2] = mlx_xpm_file_to_image(mlx, "bonuses/tex_sprites/shrek_wazowski_mouseopen.xpm", &w, &h);
	while (i < SPRITE_FRAMES)
	{
		if (!sprite->img[i])
			return (0);
		i++;
	}
	return (1);
}
