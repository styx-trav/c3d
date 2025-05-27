#ifndef LIBGRAPHIC_H
# define LIBGRAPHIC_H

# include "mlx.h"
# include <stdlib.h>

# define WIN_W 1280
# define WIN_H 720

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game {
	t_mlx	mlx;
    t_img	img;
}	t_game;

int	init_game(t_game *game);
int	close_game(t_game *game);
int	key_press(int keycode, t_game *game);

#endif