#include "liball.h"

static void	draw_floor_ceiling(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, all->ceiling, &all->fg);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, all->floor, &all->fg);
			x++;
		}
		y++;
	}
}

static void	switch_img(t_all *all)
{
	t_img	*fg;
	t_img	*bg;
	void	*tmp_ptr;
	int		tmp;

	fg = &all->fg;
	bg = &all->bg;
	tmp = fg->bpp;
	fg->bpp = bg->bpp;
	bg->bpp = tmp;
	tmp = fg->size_line;
	fg->size_line = bg->size_line;
	bg->size_line = tmp;
	tmp = fg->endian;
	fg->endian = bg->endian;
	bg->endian = tmp;
	tmp_ptr = (void *)fg->addr;
	fg->addr = bg->addr;
	bg->addr = (char *)tmp_ptr;
	tmp_ptr = fg->img;
	fg->img = bg->img;
	bg->img = tmp_ptr;
}

int	draw_loop(t_all *all)
{
	t_player	*player;

	player = &all->player;
	move_player(all, player);
	switch_img(all);
	draw_floor_ceiling(all);
	all->door.seen = false;
	if (all->map[(int)all->player.y][(int)all->player.x] == '*'
		|| all->map[(int)(all->player.y - 0.2)][(int)all->player.x] == '*'
		|| all->map[(int)all->player.y][(int)(all->player.x - 0.2)] == '*'
		|| all->map[(int)all->player.y][(int)(all->player.x + 0.2)] == '*'
		|| all->map[(int)(all->player.y + 0.2)][(int)all->player.x] == '*')
		all->see_3 = false;
	else
		all->see_3 = true;
	draw_rays(all, player);
	mlx_put_image_to_window(all->mlx, all->win, all->fg.img, 0, 0);
	return (0);
}
