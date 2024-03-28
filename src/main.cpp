// #include "./minilibx/mlx.h"
#include "../include/Color.hpp"
#include "../include/MlxBase.hpp"
#include "../include/Vector.hpp"
#include "../include/Ray.hpp"
#include "../include/Color.hpp"
// #define WIDTH 1920
// #define HEIGHT 1080

// class scene
// {
// 	public:
// 		t_canvas		canvas;
// 		t_camera		camera;
// 		t_object		*world;
// 		t_object		*light;
// 		t_vector		ambient;
// 		t_ray			ray;
// 		t_hit_record	rec;
// 	// 위 구조체들 일단 하나씩 올려놓기
// };

int main()
{
	// check_arg(argc, argv);
	Mlx *mlx = new Mlx();
	// scene = new scene();
	// draw(mlx, scene);
	// event_hooker(mlx.get_win());
	// free_all(mlx, scene);
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		write_color(*mlx, Vector((double)i / (WIDTH*HEIGHT),(double) i / (WIDTH*HEIGHT), 0.0), i % WIDTH, i / WIDTH);
	}
	mlx->put_image_to_window();
	mlx->loop_window();
	return (0);
}