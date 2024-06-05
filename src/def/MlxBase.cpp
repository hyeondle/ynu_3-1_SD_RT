#include "../../include/MlxBase.hpp"

extern "C" {
	#include "../../minilibx/mlx.h"
}

Mlx::Mlx()
{
	mmlx_init();
}

Mlx::~Mlx()
{
	mlx_destroy_window(mlx, win);
}

void *Mlx::get_win()
{
	return (win);
}

void Mlx::mmlx_init()
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, (char *)"my_mlx");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
}

void	*Mlx::get_mlx()
{
	return (mlx);
}

void	*Mlx::get_img()
{
	return (img);
}

char	*Mlx::get_addr()
{
	return (addr);
}

int	Mlx::get_bits_per_pixel()
{
	return (bits_per_pixel);
}

int	Mlx::get_line_length()
{
	return (line_length);
}

int	Mlx::get_endian()
{
	return (endian);
}

void	Mlx::locate_pixel(int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	Mlx::put_image_to_window()
{
	mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void	Mlx::loop_window()
{
	mlx_loop(mlx);
}

void	Mlx::hooker() {
	
}