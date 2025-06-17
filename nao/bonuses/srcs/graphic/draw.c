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

// void draw_square(int size, int x, int y_center, t_all *all)
// {
//     int i;
// 	int j;

// 	i = y_center - size / 2;
//     while (i < y_center + size / 2)
//     {
//         j = x - size / 2;
//         while (j < x + size / 2)
//         {
//             if (i >= 0 && j >= 0 && i < HEIGHT && j < WIDTH)
//                 put_pixel(j, i, 0x00FF0000, &all->fg);
//             j++;
//         }
//         i++;
//     }
// }

// #include <stdio.h>

// void draw_sprite_light(t_all *all, t_player *player)
// {
//     double sprite_x = all->sprite.x;
//     double sprite_y = all->sprite.y;
//     double dx = sprite_x - player->x;
//     double dy = sprite_y - player->y;
//     double dir_x = cos(player->angle);
//     double dir_y = sin(player->angle);
//     double plane_x = -dir_y * 0.66;
//     double plane_y = dir_x * 0.66;
//     double inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
//     double transform_x = inv_det * (dir_y * dx - dir_x * dy);
//     double transform_y = inv_det * (-plane_y * dx + plane_x * dy);

//     int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
//     int sprite_size = abs((int)(HEIGHT / transform_y));
//     if (transform_y <= 0)
//         return;
//     if (sprite_size <= 0 || sprite_size > HEIGHT * 4)
//         return;
//     if (sprite_screen_x < -sprite_size || sprite_screen_x > WIDTH + sprite_size)
//         return;

//     int sprite_screen_y = HEIGHT / 2;

//     draw_square(sprite_size, sprite_screen_x, sprite_screen_y, all);
// }


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
	//draw_sprite_light(all, player);
	draw_all_sprites(all, player);
	// printf("Player pos: (%f, %f) angle: %f\n", all->player.x, all->player.y, all->player.angle);
	// printf("Sprite pos: (%f, %f)\n", all->sprite.x, all->sprite.y);
	mlx_put_image_to_window(all->mlx, all->win, all->fg.img, 0, 0);
	return (0);
}
