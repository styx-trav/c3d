#include "liball.h"

static void draw_floor_ceiling(t_all *all)
{
	int x;
	int y;

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while(x < WIDTH)
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
		while(x < WIDTH)
		{
			put_pixel(x, y, all->floor, &all->fg);
			x++;
		}
		y++;
	}
}

int draw_loop(t_all *all)
{
	t_player *player = &all->player;
	
	move_player(all, player);
	mlx_destroy_image(all->mlx, all->fg.img);
	all->fg.img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	img_address(&all->fg);
	clear_image(all);
	draw_square(0, 0, 4, 0x00FF00, &(player->img));
	draw_floor_ceiling(all);
	draw_rays(all, player);
	return (0);
}
