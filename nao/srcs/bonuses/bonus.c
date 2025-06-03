void	init_map(t_all *all)
{
	t_img *img;
	int	i;
	int	j;

	img = &all->north;
	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				mlx_put_image_to_window(all->mlx, all->win, img->img, j * img->width, i * img->height);
			j++;
		}
		i++;
	}
}

void draw_square(int x, int y, int size, int color, t_img *img)
{
	int i;

	i = 0;
	if (!img || !img->addr)
		return;
	while(++i < size)
		put_pixel(x + i, y, color, img);
	i = 0;
	while(++i < size)
		put_pixel(x, y + i, color, img);
	i = 0;
	while(++i < size)
		put_pixel(x + size, y + i, color, img);
	i = 0;
	while(++i < size)
		put_pixel(x + i, y + size, color, img);
}

int touch(float px, float py, t_all *all)
{
	int x = (int)(px);
	int y = (int)(py);
	int mapx = x / 64;
	int mapy = y / 64;

	if (mapy < 0 || mapx < 0 || !all->map[mapy] || mapx >= (int)ft_strlen(all->map[mapy]) || all->map[mapy][mapx] == '\0')
		return (1);
	if (all->map[mapy][mapx] == '1' || all->map[mapy][mapx] == ' ')
		return (1);
	return (collision_zone(all, px, py));
}

void draw_one_ray(float angle, t_all *all, t_player *player)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	while(!touch(ray_x, ray_y, all))
	{
		put_pixel((int)ray_x, (int)ray_y, 0xFF0000, &all->fg);
		ray_x -= cos_angle;
		ray_y -= sin_angle;
	}
}

//init_map(all);
//mlx_put_image_to_window(all->mlx, all->win, all->player.img.img, all->player.x, all->player.y);
// ray_x = player->x - (cos_angle * dist);
// ray_y = player->y - (sin_angle * dist);
// put_pixel(ray_x, ray_y, 0x0000FF, &all->fg);

all->player.img.img = mlx_new_image(all->mlx, 10, 10);
if (!all->player.img.img)
	return (0);
all->player.img.width = 10;
all->player.img.height = 10;
