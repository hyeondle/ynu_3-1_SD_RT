#ifndef MLXBASE_HPP
#define MLXBASE_HPP

#include "MlxKeyList.hpp"

#ifndef WIDTH
	#define WIDTH 480
#endif
#ifndef HEIGHT
	#define HEIGHT WIDTH * 9 / 16
#endif
#ifndef DELTA
	#define DELTA 1.0
#endif

class camera;
class hittable;
class Mlx;

struct hook_params {
    camera *cam;
    hittable *world;
    Mlx *mlx;
};

class Mlx
{
	private:
		void	*mlx;
		void	*win;
		void	*img;
		char	*addr;
		int		bits_per_pixel;
		int		line_length;
		int		endian;
	public:
		Mlx();
		~Mlx();
		void	mmlx_init();
		void	*get_mlx();
		void	*get_win();
		void	*get_img();
		char	*get_addr();
		int		get_bits_per_pixel();
		int		get_line_length();
		int		get_endian();
	public:
		void	locate_pixel(int x, int y, int color);
		void	put_image_to_window();
		void	loop_window();

		static int hooking_event(int keycode, void *param);
		static int press_event(int keycode, void *param);
        static void key_hook(Mlx *mlx, camera &cam, hittable &world);
};

// extern "C" void key_hook(Mlx *mlx, camera &cam, hittable &world);
// extern "C" int hooking_event(int keycode, camera &cam);

#endif