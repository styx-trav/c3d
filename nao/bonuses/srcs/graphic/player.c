#include "liball.h"

void	init_player(t_all *all, t_player *player)
{
	(void)all;
	player->x = player->x + 0.5;
	player->y = player->y + 0.5;
	player->angle = PI / 2;
	if (all->dir == 'E')
		player->angle = PI;
	else if (all->dir == 'W')
		player->angle = 0;
	else if (all->dir == 'S')
		player->angle = 3 * PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	rotate_player(t_player *player)
{
	float	angle_speed;

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

static void	move_vert(t_all *all, t_player *player, float cos, float sin)
{
	float	x;
	float	y;

	x = player->x;
	y = player->y;
	if (player->key_up
		&& !collision_zone(all, x - cos, y - sin))
	{
		x -= cos;
		y -= sin;
	}
	if (player->key_down
		&& !collision_zone(all, x + cos, y + sin))
	{
		x += cos;
		y += sin;
	}
	player->x = x;
	player->y = y;
}

static void	move_hor(t_all *all, t_player *player, float cos, float sin)
{
	float	x;
	float	y;

	x = player->x;
	y = player->y;
	if (player->key_left
		&& !collision_zone(all, x - sin, y + cos))
	{
		x -= sin;
		y += cos;
	}
	if (player->key_right
		&& !collision_zone(all, x + sin, y - cos))
	{
		x += sin;
		y -= cos;
	}
	player->x = x;
	player->y = y;
}

void	move_player(t_all *all, t_player *player)
{
	float	cos_a;
	float	sin_a;

	rotate_player(player);
	cos_a = cos(player->angle) * 0.02;
	sin_a = sin(player->angle) * 0.02;
	move_vert(all, player, cos_a, sin_a);
	move_hor(all, player, cos_a, sin_a);
}
