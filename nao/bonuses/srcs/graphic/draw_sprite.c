/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:21:07 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:21:08 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liball.h"
#include "raycasting.h"

static void	draw_s_column(int x, int s_size, t_img *t, t_all *all)
{
	int		y;
	int		end_y;
	int		d;
	int		tex_y;
	char	*px;

	y = HEIGHT / 2 - s_size / 2;
	end_y = y + s_size;
	while (y < end_y)
	{
		if (y >= 0 && y < HEIGHT)
		{
			d = y * 256 - HEIGHT * 128 + s_size * 128;
			tex_y = (d * t->height) / (s_size * 256);
			if (tex_y < 0)
				tex_y = 0;
			else if (tex_y >= t->height)
				tex_y = t->height - 1;
			px = t->addr + (tex_y * t->size_line + t->tex_x * (t->bpp / 8));
			if ((*(unsigned int *)px & 0x00FFFFFF) != 0
				&& (y > all->minimap_h || x > all->minimap_w))
				put_pixel(x, y, *(unsigned int *)px, &all->fg);
		}
		y++;
	}
}

static void	get_sprite_screen_data(t_sprite *sprite, t_player *player)
{
	double	dx;
	double	dy;
	double	dir_x;
	double	dir_y;
	double	angle;

	dx = sprite->x - player->x;
	dy = sprite->y - player->y;
	dir_x = cos(player->angle);
	dir_y = sin(player->angle);
	angle = atan2(dir_x * dy - dir_y * dx, dir_x * dx + dir_y * dy);
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	sprite->dist = sqrt(dx * dx + dy * dy);
	sprite->screen_x = (int)((angle - (PI - (PI / 2.5) / 2))
			/ ((PI / 2.5) / WIDTH));
	sprite->size = (int)(HEIGHT / sprite->dist);
}

static void	draw_sprite_visible_columns(t_all *all, t_sprite *sprite)
{
	int		x;
	int		end_x;
	t_img	*tex;
	int		tex_x;

	x = sprite->screen_x - sprite->size / 2;
	end_x = sprite->screen_x + sprite->size / 2;
	tex = &sprite->img[sprite->frame_index];
	while (x < end_x)
	{
		if (x >= 0 && x < WIDTH && sprite->dist < all->z_buffer[x])
		{
			tex_x = get_sprite_tex_x(sprite->screen_x, sprite->size, x, tex);
			tex->tex_x = tex_x;
			draw_s_column(x, sprite->size, tex, all);
		}
		x++;
	}
}

static void	draw_sprite(t_all *all, t_player *player, t_sprite *sprite)
{
	if (sprite->x == -1)
		return ;
	if (!sprite || !sprite->img[sprite->frame_index].img)
		return ;
	get_sprite_screen_data(sprite, player);
	if (sprite->dist < 0.1 || sprite->size <= 0 || sprite->size > HEIGHT * 4)
		return ;
	draw_sprite_visible_columns(all, sprite);
}

void	draw_all_sprites(t_all *all, t_player *player)
{
	int	i;

	i = 0;
	while (i < all->sprite_count)
	{
		update_sprite(&all->sprites[i]);
		get_sprite_screen_data(&all->sprites[i], player);
		i++;
	}
	sort_sprites_by_distance(all->sprites, all->sprite_count);
	i = 0;
	while (i < all->sprite_count)
	{
		draw_sprite(all, player, &all->sprites[i]);
		i++;
	}
}
