#include "liball.h"

void init_player(t_all *all, t_player *player)
{
	player->x = player->x * 64 + 32 - 5;
	player->y = player->y * 64 + 32 - 5;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	draw_square(0, 0, 5, 0x00FF00, &(player->img));
	clear_image(all);
}

int key_press(int keycode, t_all *all)
{
	if (keycode == 65307)// esc
	{
		mlx_loop_end(all->mlx);
		return (0);
	}
	if(keycode == W)
		all->player.key_up = true;
	if(keycode == S)
		all->player.key_down = true;
	if(keycode == A)
		all->player.key_left = true;
	if(keycode == D)
		all->player.key_right = true;
	move_player(all, &(all->player));
	return (0);
}

int key_release(int keycode, t_all *all)
{
	if(keycode == W)
		all->player.key_up = false;
	if(keycode == S)
		all->player.key_down = false;
	if(keycode == A)
		all->player.key_left = false;
	if(keycode == D)
		all->player.key_right = false;
	return (0);
}

void move_player(t_all *all, t_player *player)
{
	int speed;

	speed = 5;
	if (player->key_up && all->map[(int)((player->y - speed) / 64)][(int)(player->x / 64)] != '1')
		player->y -= speed;
	if (player->key_down && all->map[(int)((player->y + speed) / 64)][(int)(player->x / 64)] != '1')
		player->y += speed;
	if (player->key_left && all->map[(int)(player->y / 64)][(int)((player->x - speed) / 64)] != '1')
		player->x -= speed;
	if (player->key_right && all->map[(int)(player->y / 64)][(int)((player->x + speed) / 64)] != '1')
		player->x += speed;
	clear_image(all);
}
