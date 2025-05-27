#include "libgraphic.h"

int	init_game(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (1);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WIN_W, WIN_H, "cub3D");
	if (!game->mlx.win_ptr)
		return (1);
	game->img.img_ptr = NULL;
	game->img.addr = NULL;
	game->img.bpp = 0;
	game->img.line_len = 0;
	game->img.endian = 0;
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	return (0);
}

static void	free_game(t_game *game)
{
	if (!game)
		return;
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}