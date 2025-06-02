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
static bool collision_zone(t_all *all, float px, float py)
{
	float zone;
	float dy;
	float dx;
	int check_x;
	int check_y;

	zone = 10.0f;
	dy = -zone;
	while (dy <= zone)
	{
		dx = -zone;
		while (dx <= zone)
		{
			check_x = (int)((px + dx) / 64);
			check_y = (int)((py + dy) / 64);
			if (check_y < 0 || check_x < 0 || !all->map[check_y] || check_x >= (int)ft_strlen(all->map[check_y]) || all->map[check_y][check_x] == '\0')
				return (true);
			if (all->map[check_y][check_x] == '1' || all->map[check_y][check_x] == ' ')
				return (true);
			dx += zone;
		}
		dy += zone;
	}
	return (false);
}

bool touch(float px, float py, t_all *all)
{
	int x = (int)(px);
	int y = (int)(py);
	int mapx = x / 64;
	int mapy = y / 64;

	if (mapy < 0 || mapx < 0 || !all->map[mapy] || mapx >= (int)ft_strlen(all->map[mapy]) || all->map[mapy][mapx] == '\0')
		return (true);
	if (all->map[mapy][mapx] == '1' || all->map[mapy][mapx] == ' ')
		return (true);
	return (collision_zone(all, px, py));
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
