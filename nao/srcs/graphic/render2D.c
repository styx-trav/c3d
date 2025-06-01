#include "liball.h"

void	init_map(t_all *all)
{
	t_img *img;
	int	i;
	int	j;

	img = &all->north;
	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				mlx_put_image_to_window(all->mlx, all->win, img->img, j * img->width, i * img->height);
			j++;
		}
		i++;
	}
}
bool touch(float px, float py, t_all *all)
{
	int x;
	int y;
	int i;
	int j;

	x = px / 64;
	y = py / 64;
	//printf("%d, %d\n", x, y);
	i = 0;
	while (all->map[i])
		i++;
	j = 0;
	while (all->map[0][j])
		j++;
	if (x >= j - 1 || y >= i - 1
		|| all->map[y][x] == '1' || all->map[y][x] == ' ')
		return (true);
	return (false);
}

void clear_image(t_all *all)
{
	mlx_put_image_to_window(all->mlx, all->win, all->fg.img, 0, 0);
	//init_map(all);
	//mlx_put_image_to_window(all->mlx, all->win, all->player.img.img, all->player.x, all->player.y);
}

void put_pixel(int x, int y, int color, t_img *img)
{
	int index;

	if (!img || !img->addr || x < 0 || y < 0 || x >= img->width || y >= img->height)
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
	if (!img || !img->addr)
		return;
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
