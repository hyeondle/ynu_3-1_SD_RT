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

double hit_sphere(const Point &center, double radius, const Ray &r) {
	Vector oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b*b - 4*a*c;

	if (discriminant < 0) {
		return -1.0;
	} else {
		// std::cout << "hit " << (-b - sqrt(discriminant)) / (2.0 * a) << std::endl;
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

Color ray_color(const Ray &r) {
	auto t = hit_sphere(Point(0,0,-1), 0.5, r);
	if (t > 0.0) {
		Vector N = unit(r.at(t) - Vector(0,0,-1));
		return 0.5 * Color(N.x()+1, N.y()+1, N.z()+1);
	}

	Vector unit_direction = unit(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
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

	// cam
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = Point(0, 0, 0);

	// calcaulate vector across hor, down the vert viewport edges
	auto viewport_u = Vector(viewport_width, 0, 0);
	auto viewport_v = Vector(0, -viewport_height, 0);

	//
	auto pixel_delta_u = viewport_u / double(image_width);
	auto pixel_delta_v = viewport_v / double(image_height);

	// cal location
	auto viewport_upper_left = camera_center - Vector(0,0,focal_length) - viewport_u/2 - viewport_v/2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// render

	for (int j = 0; j < image_height; j++) {
		for (int i = 0; i < WIDTH; i++)
		{
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			Ray r(camera_center, ray_direction);

			Color pixel_color = ray_color(r);
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