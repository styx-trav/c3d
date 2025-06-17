#include "liball.h"
#include "raycasting.h"

static int	get_sprite_tex_x(int sprite_screen_x, int sprite_size, int x, t_img *tex)
{
	int relative_x = x - (sprite_screen_x - sprite_size / 2);
	int tex_x = (relative_x * tex->width) / sprite_size;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return tex_x;
}

static void	draw_sprite_column(int x, int sprite_size, int sprite_screen_y, int tex_x, t_img *tex, t_all *all)
{
	int y_start = sprite_screen_y - sprite_size / 2;
	int y_end = y_start + sprite_size;
	int y = y_start;
	int d, tex_y;
	char *px;
	int color;

	if (!tex || !tex->addr)
		return;
	while (y < y_end)
	{
		if (y >= 0 && y < HEIGHT)
		{
			d = y * 256 - HEIGHT * 128 + sprite_size * 128;
			tex_y = (d * tex->height) / (sprite_size * 256);
			if (tex_y < 0)
				tex_y = 0;
			else if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			px = tex->addr + (tex_y * tex->size_line + tex_x * (tex->bpp / 8));
			color = *(unsigned int *)px;
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(x, y, color, &all->fg);
		}
		y++;
	}
}

void	draw_sprite(t_all *all, t_player *player, t_sprite *sprite)
{
	double dx = sprite->x - player->x;
	double dy = sprite->y - player->y;
	double dir_x = cos(player->angle);
	double dir_y = sin(player->angle);
	double plane_x = -dir_y * PI / 2;
	double plane_y = dir_x * PI / 2;
	double inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
	double transform_x = inv_det * (dir_y * dx - dir_x * dy);
	double transform_y = inv_det * (-plane_y * dx + plane_x * dy);

	if (!sprite || !sprite->img[sprite->frame_index].img)
		return;
	else if (transform_y <= 0.1)
		return;
	int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	int sprite_size = (int)(HEIGHT * transform_y);

	if (sprite_size <= 0 || sprite_size > HEIGHT * 4)
		return;
	int sprite_screen_y = HEIGHT / 2;

	int draw_start_x = sprite_screen_x - sprite_size / 2;
	int draw_end_x = sprite_screen_x + sprite_size / 2;
	int x = draw_start_x;
	while (x < draw_end_x)
	{
		if (x >= 0 && x < WIDTH)
		{
			t_img *tex = &sprite->img[sprite->frame_index];
			int tex_x = get_sprite_tex_x(sprite_screen_x, sprite_size, x, tex);
			draw_sprite_column(x, sprite_size, sprite_screen_y, tex_x, tex, all);
		}
		x++;
	}
}

void	draw_all_sprites(t_all *all, t_player *player)
{
	update_sprite(&all->sprite);
	draw_sprite(all, player, &all->sprite);
}
