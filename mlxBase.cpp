#include "./mlxBase.hpp"

extern "C" {
	#include "./minilibx/mlx.h"
	}

void *mlx_base::get_win()
{
	return (win);
}

void mlx_base::mmlx_init()
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char *)"my_mlx");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
}

void	*mlx_base::get_mlx()
{
	return (mlx);
}

void	*mlx_base::get_img()
{
	return (img);
}

char	*mlx_base::get_addr()
{
	return (addr);
}

int	mlx_base::get_bits_per_pixel()
{
	return (bits_per_pixel);
}

int	mlx_base::get_line_length()
{
	return (line_length);
}

int	mlx_base::get_endian()
{
	return (endian);
}

mlx_base::mlx_base()
{
	mmlx_init();
}

mlx_base::~mlx_base()
{
	mlx_destroy_window(mlx, win);
}

void	mlx_base::locate_pixel(int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mlx_base::put_image_to_window()
{
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void	mlx_base::loop_window()
{
	mlx_loop(mlx);
}