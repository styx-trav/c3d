/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltantin <ltantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:20:54 by ltantin           #+#    #+#             */
/*   Updated: 2025/06/26 16:20:55 by ltantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liball.h"

int	load_sprite_frames(t_sprite *sprite, void *mlx)
{
	int		w;
	int		h;
	int		i;
	char	*paths[SPRITE_FRAMES];

	paths[0] = "bonuses/tex_sprites/shrek_wazowski_eyesclosed.xpm";
	paths[1] = "bonuses/tex_sprites/shrek_wazowski.xpm";
	paths[2] = "bonuses/tex_sprites/shrek_wazowski_mouseopen.xpm";
	i = 0;
	sprite->frame_index = 0;
	sprite->last_update = get_current_time_ms();
	while (i < SPRITE_FRAMES)
	{
		sprite->img[i].img = mlx_xpm_file_to_image(mlx, paths[i], &w, &h);
		if (!sprite->img[i].img)
			return (0);
		sprite->img[i].addr = mlx_get_data_addr(sprite->img[i].img,
				&sprite->img[i].bpp, &sprite->img[i].size_line,
				&sprite->img[i].endian);
		sprite->img[i].width = w;
		sprite->img[i].height = h;
		i++;
	}
	return (1);
}

void	update_sprite(t_sprite *sprite)
{
	unsigned long	now;

	now = get_current_time_ms();
	if (now - sprite->last_update > 100)
	{
		sprite->frame_index = (sprite->frame_index + 1) % SPRITE_FRAMES;
		sprite->last_update = now;
	}
}

static int	process_sprite(t_all *all, int i, int j, int *id)
{
	if (all->map[i][j] == 'S')
	{
		all->sprites[*id].x = j + 0.5;
		all->sprites[*id].y = i + 0.5;
		if (!load_sprite_frames(&all->sprites[*id], all->mlx))
			return (0);
		(*id)++;
	}
	return (1);
}

int	init_sprites(t_all *all)
{
	int	i;
	int	j;
	int	id;
	int	count;

	id = 0;
	count = count_sprites(all->map);
	all->sprite_count = count;
	all->sprites = malloc(sizeof(t_sprite) * count);
	if (!all->sprites)
		return (0);
	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (!process_sprite(all, i, j, &id))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
