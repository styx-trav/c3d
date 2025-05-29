#include "liball.h"
#include <stdio.h>

void init_player(t_all *all, t_player *player)
{
	(void)all;
	player->x = player->x * 64 + 32 - 5;
	player->y = player->y * 64 + 32 - 5;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
	//draw_square(0, 0, 4, 0x00FF00, &(player->img));
	//clear_image(all);
}

int key_press(int keycode, t_all *all)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == 65307)// esc
	{
		mlx_loop_end(all->mlx);
		return (0);
	}
	if (keycode == W)
		all->player.key_up = true;
	if (keycode == S)
		all->player.key_down = true;
	if (keycode == A)
		all->player.key_left = true;
	if (keycode == D)
		all->player.key_right = true;
	if (keycode == LEFT)
		all->player.left_rotate = true;
	if (keycode == RIGHT)
		all->player.right_rotate = true;
	//move_player(all, &(all->player));
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
	if (keycode == LEFT)
		all->player.left_rotate = false;
	if (keycode == RIGHT)
		all->player.right_rotate = false;
	return (0);
}

void rotate_player(t_player *player)
{
	float angle_speed;

	angle_speed = 0.008;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}
void move_player(t_all *all, t_player *player)
{
	float speed;
	float cos_angle;
	float sin_angle;

	speed = 0.2;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	//printf("show me angle %9.6f and cos %9.6f, and sin %9.6f\n", player->angle, cos_angle, sin_angle);
	if (player->key_up && all->map[(int)((player->y - speed) / 64)][(int)(player->x / 64)] != '1')
	{
		//player->y -= speed;
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
		
	}
	if (player->key_down && all->map[(int)((player->y + speed) / 64)][(int)(player->x / 64)] != '1')
	{
		//player->y += speed;
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_left && all->map[(int)(player->y / 64)][(int)((player->x - speed) / 64)] != '1')
	{
		//player->x -= speed;
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (player->key_right && all->map[(int)(player->y / 64)][(int)((player->x + speed) / 64)] != '1')
	{
		//player->x += speed;
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	//clear_image(all);
}
