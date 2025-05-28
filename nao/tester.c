#include "libparsing.h"
#include "libmap.h"
#include "liball.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s\n", map[i]);
		free(map[i]);
		i++;
	}
	if (map)
		free(map);
}

void	print_map(t_maps *map)
{
	printf("current map :: player at %d, %d, min %d, %d, max %d, %d\n", map->i, map->j, map->mini, map->minj, map->maxi, map->maxj);
	free_map(map->map);
	free(map);
}

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

int	exitt(t_all *str)
{
	mlx_loop_end(str->mlx);
	return (0);
}

int	closer(int keycode, t_all *str)
{
	if (keycode == 0xff1b)
		mlx_loop_end(str->mlx);
	return (0);
}

void	start_loop(t_all *all)
{
	mlx_hook(all->win, 2, 1L << 0, key_press, all);
	mlx_hook(all->win, 3, 1L << 1, key_release, all);
	mlx_hook(all->win, 17, 0, &exitt, all);

	mlx_loop_hook(all->mlx, draw_loop, all);
	mlx_loop(all->mlx);
}

int	main(void)
{
	t_all all;

	if (!init(&all, "texte.cub", WIDTH, HEIGHT))
		return (0);
	init_player(&all.player);
	start_loop(&all);
	free_all(&all);
	return (0);
}
