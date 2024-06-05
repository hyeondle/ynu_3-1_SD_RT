#include "../../include/MlxBase.hpp"
#include "Camera.hpp"
#include "HitRecord.hpp"

extern "C" {
	#include "mlx.h"

	int Mlx::hooking_event(int keycode, void *param) {
        hook_params *params = static_cast<hook_params*>(param);
        camera *cam = params->cam;
        hittable *world = params->world;
        Mlx *mlx = params->mlx;

        if (keycode == KEY_W) {
            cam->move_camera_x(DELTA, *world, mlx);
        } else if (keycode == KEY_A) {
            cam->move_camera_y(-DELTA, *world, mlx);
        } else if (keycode == KEY_S) {
            cam->move_camera_x(-DELTA, *world, mlx);
        } else if (keycode == KEY_D) {
            cam->move_camera_y(DELTA, *world, mlx);
        } else if (keycode == KEY_Q) {
            cam->move_camera_z(DELTA, *world, mlx);
        } else if (keycode == KEY_E) {
            cam->move_camera_z(-DELTA, *world, mlx);
        }
        return 0;
    }

	int Mlx::press_event(int keycode, void *param) {
		hook_params *params = static_cast<hook_params*>(param);
		camera *cam = params->cam;
		hittable *world = params->world;
		Mlx *mlx = params->mlx;

		if (keycode == KEY_T) {
			cam->samples_per_pixel = 50;
			cam->max_depth = 10;
			cam->render(*world, mlx);
		} else if (keycode == KEY_Y) {
			cam->samples_per_pixel = 1;
			cam->max_depth = 2;
			cam->render(*world, mlx);
		}
		return 0;
	}

    void Mlx::key_hook(Mlx *mlx, camera &cam, hittable &world) {
		hook_params *params = new hook_params{&cam, &world, mlx};
        mlx_hook(mlx->get_win(), 2, 2, (int (*)(void))hooking_event, params);
		mlx_key_hook(mlx->get_win(), (int (*)(void))press_event, params);
    }
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
