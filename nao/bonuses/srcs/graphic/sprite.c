#include "liball.h"

void	get_sprite(t_all *all)
{
	int i = 0;
	while (all->map[i])
	{
		int j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'M')
			{
				all->sprite.x = j + 0.5;
				all->sprite.y = i + 0.5;
				return;
			}
			j++;
		}
		i++;
	}
}


int load_sprite_frames(t_sprite *sprite, void *mlx)
{
	int w;
	int h;
	int i = 0;

	sprite->frame_index = 0;
	sprite->last_update = get_current_time_ms();
	sprite->img[0] = mlx_xpm_file_to_image(mlx, "bonuses/tex_sprites/shrek_wazowski_eyesclosed.xpm", &w, &h);
	sprite->img[1] = mlx_xpm_file_to_image(mlx, "bonuses/tex_sprites/shrek_wazowski.xpm", &w, &h);
	sprite->img[2] = mlx_xpm_file_to_image(mlx, "bonuses/tex_sprites/shrek_wazowski_mouseopen.xpm", &w, &h);
	while (i < SPRITE_FRAMES)
	{
		if (!sprite->img[i])
			return (0);
		i++;
	}
	return (1);
}

void update_sprite(t_sprite *sprite)
{
	unsigned long now;

	now = get_current_time_ms();
	if (now - sprite->last_update > 100) 
	{
		sprite->frame_index = (sprite->frame_index + 1) % SPRITE_FRAMES;
		sprite->last_update = now;
	}
}

// void	draw_sprite(t_all *all)
// {
// 	int	screen_x;
// 	int	screen_y;

// 	screen_x = all->sprite.x * 10;
// 	screen_y = all->sprite.y * 10;
// 	mlx_put_image_to_window(all->mlx, all->win,
// 		all->sprite.img[all->sprite.frame_index], screen_x, screen_y);
// }

