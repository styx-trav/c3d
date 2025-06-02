#include "liball.h"

int	key_press(int keycode, t_all *all)
{
	if (keycode == 65307)
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
	return (0);
}

int	key_release(int keycode, t_all *all)
{
	if (keycode == W)
		all->player.key_up = false;
	if (keycode == S)
		all->player.key_down = false;
	if (keycode == A)
		all->player.key_left = false;
	if (keycode == D)
		all->player.key_right = false;
	if (keycode == LEFT)
		all->player.left_rotate = false;
	if (keycode == RIGHT)
		all->player.right_rotate = false;
	return (0);
}
