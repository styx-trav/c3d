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
