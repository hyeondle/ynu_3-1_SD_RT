// #include "./minilibx/mlx.h"
#include "../include/RTSet.hpp"

#include "../include/MlxBase.hpp"
#include "../include/HitRecord.hpp"
#include "../include/HitList.hpp"
#include "../include/Sphere.hpp"

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


color ray_color(const ray &r, const hittable &world) {
	hit_record rec;
	if (world.hit(r, interval(0, infinity), rec)) {
		return 0.5 * (rec.normal + color(1,1,1));
	}

	vector unit_direction = unit(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}


int main()
{

	Mlx *mlx = new Mlx();

	//
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = WIDTH;

	//
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// world
	hittable_list world;

	world.add(make_shared<sphere>(point(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point(0, -100.5, -1), 100));

	// cam
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point(0, 0, 0);

	// calcaulate vector across hor, down the vert viewport edges
	auto viewport_u = vector(viewport_width, 0, 0);
	auto viewport_v = vector(0, -viewport_height, 0);

	//
	auto pixel_delta_u = viewport_u / double(image_width);
	auto pixel_delta_v = viewport_v / double(image_height);

	// cal location
	auto viewport_upper_left = camera_center - vector(0,0,focal_length) - viewport_u/2 - viewport_v/2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// render

	for (int j = 0; j < image_height; j++) {
		for (int i = 0; i < WIDTH; i++)
		{
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r, world);
			write_color(*mlx, pixel_color, i, j);
		}
	}
	mlx->put_image_to_window();
	mlx->loop_window();
	return (0);
}


// int main()
// {
// 	// check_arg(argc, argv);
// 	Mlx *mlx = new Mlx();
// 	// scene = new scene();
// 	// draw(mlx, scene);
// 	// event_hooker(mlx.get_win());
// 	// free_all(mlx, scene);
// 	for (int i = 0; i < WIDTH * HEIGHT; i++)
// 	{
// 		write_color(*mlx, Vector((double)i / (WIDTH*HEIGHT),(double) i / (WIDTH*HEIGHT), 0.0), i % WIDTH, i / WIDTH);
// 	}
// 	mlx->put_image_to_window();
// 	mlx->loop_window();
// 	return (0);
// }