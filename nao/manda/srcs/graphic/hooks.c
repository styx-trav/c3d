/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naorakot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:24:35 by naorakot          #+#    #+#             */
/*   Updated: 2025/06/11 19:24:37 by naorakot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	mouse_move(int x, int y, t_all *all)
{
	int		center_x;
	float	sensitivity;
	int		delta_x;

	(void)y;
	center_x = WIDTH / 2;
	sensitivity = 0.001;
	if (x == center_x)
		return (0);
	delta_x = x - center_x;
	all->player.angle += delta_x * sensitivity;
	if (all->player.angle > 2 * PI)
		all->player.angle = 0;
	if (all->player.angle < 0)
		all->player.angle = 2 * PI;
	mlx_mouse_move(all->mlx, all->win, center_x, HEIGHT / 2);
	return (0);
}

int	exitt(t_all *str)
{
	mlx_loop_end(str->mlx);
	return (0);
}
