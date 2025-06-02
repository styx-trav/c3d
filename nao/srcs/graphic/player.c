#include "liball.h"
#include <stdio.h>
bool collision_zone(t_all *all, float px, float py);

void init_player(t_all *all, t_player *player)
{
	(void)all;
	player->x = player->x + 0.5;//* 64 + 32 - 5;
	player->y = player->y + 0.5;//* 64 + 32 - 5;
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
		printf("places, places %d, %d\n", (int)all->player.y, (int)all->player.x);
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

	angle_speed = 0.02;
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
	float x = player->x;
	float y = player->y;

	speed = 0.02;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
		//&& all->map[(int)((y - sin_angle * speed))][(int)(x - cos_angle * speed)] != '1'
		//&& all->map[(int)((y - sin_angle * speed))][(int)(x - cos_angle * speed)] != ' ')
	{
		//player->y -= speed;
		x -= cos_angle * speed;
		y -= sin_angle * speed;
		
	}
	if (player->key_down)
		//&& all->map[(int)((y + sin_angle * speed))][(int)(x + cos_angle * speed)] != '1'
		//&& all->map[(int)((y + sin_angle * speed))][(int)(x + cos_angle * speed)] != ' ')
	{
		//player->y += speed;
		x += cos_angle * speed;
		y += sin_angle * speed;
	}
	if (player->key_left)
		//&& all->map[(int)((y + cos_angle * speed))][(int)(x - sin_angle * speed)] != '1'
		//&& all->map[(int)((y + cos_angle * speed))][(int)(x - sin_angle * speed)] != ' ')
	{
		//player->x -= speed;
		x -= sin_angle * speed;
		y += cos_angle * speed;
	}
	if (player->key_right)
		//&& all->map[(int)((y - cos_angle * speed))][(int)(x + sin_angle * speed)] != '1'
		//&& all->map[(int)((y - cos_angle * speed))][(int)(x + sin_angle * speed)] != ' ')
	{
		//player->x += speed;
		x += sin_angle * speed;
		y -= cos_angle * speed;
	}
	if (!collision_zone(all, x, y))
	{
		player->x = x;
		player->y = y;
	}
	else
		printf("collusion\n");
	//clear_image(all);
}
