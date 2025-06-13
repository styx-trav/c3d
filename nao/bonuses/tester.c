#include "libparsing.h"
#include "libmap.h"
#include "liball.h"

void	free_all(t_all *all)
{
	if (all->map)
		free_map(all->map);
	if (all->north.img)
		mlx_destroy_image(all->mlx, all->north.img);
	if (all->south.img)
		mlx_destroy_image(all->mlx, all->south.img);
	if (all->west.img)
		mlx_destroy_image(all->mlx, all->west.img);
	if (all->east.img)
		mlx_destroy_image(all->mlx, all->east.img);
	if (!all->fg.img)
		printf("Error\ninit mlx\n");
	else
		mlx_destroy_image(all->mlx, all->fg.img);
	if (all->bg.img)
		mlx_destroy_image(all->mlx, all->bg.img);
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	if (all->mlx)
		mlx_destroy_display(all->mlx);
	if (all->mlx)
		free(all->mlx);
}

void	start_loop(t_all *all)
{
	mlx_loop_hook(all->mlx, draw_loop, all);
	mlx_hook(all->win, 2, 1L << 0, key_press, all);
	mlx_hook(all->win, 3, 1L << 1, key_release, all);
	mlx_hook(all->win, 6, 1L << 6, mouse_move, all);
	mlx_mouse_hook(all->win, open_door, all);
	mlx_hook(all->win, 17, 0, &exitt, all);

	mlx_mouse_hide(all->mlx, all->win);
	mlx_loop(all->mlx);
}
/*#include <stdio.h>
void	print_map(char **map)
{
	int	i = 0;

	while (map && map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}*/

int	main(int argc, char **argv)
{ 
	t_all all;

	if (argc != 2)
		return (0);
	if (!init(&all, argv[1], WIDTH, HEIGHT))
	{
		free_all(&all);
		return (0);
	}
	//print_map(all.map);
	init_player(&all, &all.player);
	start_loop(&all);
	free_all(&all);
	return (0);
}
