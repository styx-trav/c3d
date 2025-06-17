#include "liball.h"

#include <stdio.h>

int get_sprite(t_all *all)
{
	int i = 0;
	while (all->map[i])
	{
		int j = 0;
		while (all->map[i][j])
		{
			printf("checking [%d][%d] = %c\n", i, j, all->map[i][j]);
			if (all->map[i][j] == 'M')
			{
				all->sprite.x = j + 0.5;
				all->sprite.y = i + 0.5;
				printf("FOUND SPRITE: %f %f\n", all->sprite.x, all->sprite.y);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


int load_sprite_frames(t_sprite *sprite, void *mlx)
{
    int w;
	int h;
    int i;;
    char *paths[SPRITE_FRAMES] = 
	{
        "bonuses/tex_sprites/shrek_wazowski_eyesclosed.xpm",
        "bonuses/tex_sprites/shrek_wazowski.xpm",
        "bonuses/tex_sprites/shrek_wazowski_mouseopen.xpm"
    };

	i = 0;
    sprite->frame_index = 0;
    sprite->last_update = get_current_time_ms();
    while (i < SPRITE_FRAMES)
    {
        sprite->img[i].img = mlx_xpm_file_to_image(mlx, paths[i], &w, &h);
        if (!sprite->img[i].img)
            return 0;
        sprite->img[i].addr = mlx_get_data_addr(sprite->img[i].img, &sprite->img[i].bpp,
                                               &sprite->img[i].size_line, &sprite->img[i].endian);
        sprite->img[i].width = w;
        sprite->img[i].height = h;
        i++;
    }
    return 1;
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
