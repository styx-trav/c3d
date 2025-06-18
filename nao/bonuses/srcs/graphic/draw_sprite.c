#include "liball.h"
#include "raycasting.h"

static int	get_sprite_tex_x(int sprite_screen_x, int sprite_size, int x, t_img *tex)
{
	int relative_x;
	int tex_x;

	relative_x = x - (sprite_screen_x - sprite_size / 2);
	tex_x = (relative_x * tex->width) / sprite_size;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static void	draw_sprite_column(int x, int sprite_size, int sprite_screen_y, int tex_x, t_img *tex, t_all *all)
{
	int y_start;
	int y_end;
	int y;
	int d;
	int tex_y;
	char *px;
	int color;

	y_start = sprite_screen_y - sprite_size / 2;
	y_end = y_start + sprite_size;
	y = y_start;
	if (!tex || !tex->addr)
		return ;
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

	double angle = atan2(dir_x * dy - dir_y * dx, dir_x * dx + dir_y * dy);

	if (!sprite || !sprite->img[sprite->frame_index].img)
		return;
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;

	float fov = PI / 2.5;

	int sprite_screen_x = (int)((angle - (PI - fov / 2)) / (fov / WIDTH));

	double dist = sqrt(dx * dx + dy * dy);
	if (dist < 0.1)
		return;

	double step_x = dx / dist;
	double step_y = dy / dist;
	double t = 0;
	
	while (t < dist)
	{
		int map_x = (int)(player->x + step_x * t);
		int map_y = (int)(player->y + step_y * t);

		if (map_y >= 0 && all->map[map_y] && map_x >= 0 && map_x < (int)ft_strlen(all->map[map_y]))
		{
			if (all->map[map_y][map_x] == '1' || all->map[map_y][map_x] == '?')
				return ;
		}
		t += 0.05;
	}

	int sprite_size = (int)(HEIGHT / dist);
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
