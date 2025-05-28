#include "liball.h"

void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}

int key_press(int keycode, t_all *all)
{
	if (keycode == 65307) // esc
		exit(0);
	if(keycode == W)
		all->player.key_up = true;
	if(keycode == S)
		all->player.key_down = true;
	if(keycode == A)
		all->player.key_left = true;
	if(keycode == D)
		all->player.key_right = true;
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

void move_player(t_player *player)
{
	int speed;

	speed = 5;
	if (player->key_up)
		player->y -= speed;
	if (player->key_down)
		player->y += speed;
	if (player->key_left)
		player->x -= speed;
	if (player->key_right)
		player->x += speed;
}
