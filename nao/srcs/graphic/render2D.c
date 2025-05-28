#include "liball.h"

void clear_image(t_all *all)
{
	int y;
	int x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, &all->fg);
			x++;
		}
		y++;
	}
}

int draw_loop(t_all *all)
{
	t_player *player;

	player = &all->player;
	move_player(player);
	clear_image(all);
	draw_square(player->x, player->y, 5, 0x00FF00, &all->fg);
	mlx_put_image_to_window(all->mlx, all->win, all->fg.img, 0, 0);
	return (0);
}

void put_pixel(int x, int y, int color, t_img *img)
{
	int index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->size_line + x * img->bpp / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_img *img)
{
	int i;

	i = 0;
	while(++i < size)
		put_pixel(x + i, y, color, img);
	i = 0;
	while(++i < size)
		put_pixel(x, y + i, color, img);
	i = 0;
	while(++i < size)
		put_pixel(x + size, y + i, color, img);
	i = 0;
	while(++i < size)
		put_pixel(x + i, y + size, color, img);
}
