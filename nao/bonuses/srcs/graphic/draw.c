#include "liball.h"

static void	draw_floor_ceiling(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, all->ceiling, &all->fg);
			x++;
		}
		y++;
	}
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, all->floor, &all->fg);
			x++;
		}
		y++;
	}
}

static void	switch_img(t_all *all)
{
	t_img	*fg;
	t_img	*bg;
	void	*tmp_ptr;
	int		tmp;

	fg = &all->fg;
	bg = &all->bg;
	tmp = fg->bpp;
	fg->bpp = bg->bpp;
	bg->bpp = tmp;
	tmp = fg->size_line;
	fg->size_line = bg->size_line;
	bg->size_line = tmp;
	tmp = fg->endian;
	fg->endian = bg->endian;
	bg->endian = tmp;
	tmp_ptr = (void *)fg->addr;
	fg->addr = bg->addr;
	bg->addr = (char *)tmp_ptr;
	tmp_ptr = fg->img;
	fg->img = bg->img;
	bg->img = tmp_ptr;
}

//? => angle in fov ===> (angle - (PI - fov/2)) / (fov/width);
void  draw_square(double dist, double angle, t_all *all)
{
	int size = (int)(80.0 / dist); //had to choose a size for it
	float fov = PI / 2.5;
	double res = (angle - (PI-fov/2)) / (fov/WIDTH);//basic calculation for the angle range on screen
	int x = (int)res;
	int y = HEIGHT/2;//static height for now
	int i = y - size/2;
	int j;
	while (i < y + size/2)
	{
		j = x - size/2;
		while (j < x + size/2)
		{
			if (i >0 && j >0 && i <HEIGHT && j <WIDTH)
				put_pixel(j, i, 0x00FF0000, &all->fg);
			j++;
		}
		i++;
	}
}
//not sure where the problems are coming from on the moving front :: visibly there's an angle issue to it ?
//maybe the fov inclusion, but movement makes it bug out
//definitely the fov inclusion, maybe the angle add ?
void  draw_sprite_light(t_all *all, t_player *player)
{
	double xs = 25.5;
	double ys = 11.5;
	double x = cos(player->angle);
	double y = sin(player->angle);
	double vectorx = xs - player->x;
	double vectory = ys - player->y;
	double angle = atan2(x*vectory-y*vectorx,x*vectorx+y*vectory);
	double dist = sqrt((vectorx * vectorx) + (vectory * vectory));
	while  (angle >= 2 * PI)
		angle = angle - (2 * PI);
	while  (angle < 0)
		angle = angle + (2 * PI);
	if (angle > (PI) - (PI / 5) && angle < (PI) + (PI / 5))
		draw_square(dist, angle, all);
}

int	draw_loop(t_all *all)
{
	t_player	*player;

	player = &all->player;
	move_player(all, player);
	switch_img(all);
	draw_floor_ceiling(all);
	all->door.seen = false;
	if (all->map[(int)all->player.y][(int)all->player.x] == '*'
		|| all->map[(int)(all->player.y - 0.2)][(int)all->player.x] == '*'
		|| all->map[(int)all->player.y][(int)(all->player.x - 0.2)] == '*'
		|| all->map[(int)all->player.y][(int)(all->player.x + 0.2)] == '*'
		|| all->map[(int)(all->player.y + 0.2)][(int)all->player.x] == '*')
		all->see_3 = false;
	else
		all->see_3 = true;
	update_sprite(&all->sprite);
	draw_rays(all, player);
	//nao new stuff
	draw_sprite_light(all, player);
	//draw_sprite(all);
	mlx_put_image_to_window(all->mlx, all->win, all->fg.img, 0, 0);
	return (0);
}
