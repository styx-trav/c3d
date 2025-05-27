#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>

typedef struct s_img
{
  void *img;
  int width;
  int height;
}               t_img;

typedef struct s_mlx
{
  void  *mlx;
  void  *win;
  t_img  img;
}                 t_mlx;

int	exitt(t_mlx *str)
{
	mlx_loop_end(str->mlx);
	return (0);
}

int	closer(int keycode, t_mlx *str)
{
	if (keycode == 0xff1b)
		mlx_loop_end(str->mlx);
	return (0);
}

int main()
{
  t_mlx mlx;
  mlx.mlx = mlx_init();
  mlx.win = mlx_new_window(mlx.mlx, 800, 800, "textures");
  mlx.img.img = mlx_xpm_file_to_image(mlx.mlx, "./tex.xpm", &(mlx.img.width), &(mlx.img.height));
  mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
  mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 64, 64);
  mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 128, 0);
  mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 192, 64);
  mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 256, 0);
  mlx_hook(mlx.win, 2, 1L << 0, &closer, &mlx);
  mlx_hook(mlx.win, 17, 0, &exitt, &mlx);
  mlx_loop(mlx.mlx);
  mlx_destroy_image(mlx.mlx, mlx.img.img);
  mlx_destroy_window(mlx.mlx, mlx.win);
  mlx_destroy_display(mlx.mlx);
  free(mlx.mlx);
}
