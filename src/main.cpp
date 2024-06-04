// #include "./minilibx/mlx.h"
#include "../include/RTSet.hpp"

#include "../include/Camera.hpp"
#include "../include/MlxBase.hpp"
#include "../include/HitRecord.hpp"
#include "../include/HitList.hpp"
#include "../include/Material.hpp"
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

int main()
{

	Mlx *mlx = new Mlx();

	// world
	hittable_list world;

	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = make_shared<dielectric>(1.5);
	auto material_bubble = make_shared<dielectric>(1.0/1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	world.add(make_shared<sphere>(point(0, -100.5, -1), 100, material_ground));
	world.add(make_shared<sphere>(point(0, 0, -1), 0.5, material_center));
	world.add(make_shared<sphere>(point(-1, 0, -1), 0.5, material_left));
	world.add(make_shared<sphere>(point(-1, 0, -1), 0.4, material_bubble));
	world.add(make_shared<sphere>(point(1, 0, -1), 0.5, material_right));


	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = WIDTH;
	cam.samples_per_pixel = SAMPLES_PER_PIXEL;
	cam.max_depth = MAX_DEPTH;

	cam.vfov = 20;
	cam.lookfrom = point(-2,2,1);
	cam.lookat = point(0,0,-1);
	cam.vup = vector(0,1,0);

	cam.render(world, mlx);

	mlx->put_image_to_window();
	mlx->loop_window();
	return (0);
}


// int main()
// {

// 	Mlx *mlx = new Mlx();

// 	// world
// 	hittable_list world;

// 	world.add(make_shared<sphere>(point(0, 0, -1), 0.5));
// 	world.add(make_shared<sphere>(point(0, -100.5, -1), 100));

// 	camera cam;

// 	cam.aspect_ratio = 16.0 / 9.0;
// 	cam.image_width = WIDTH;

// 	cam.render(world, mlx);

// 	mlx->put_image_to_window();
// 	mlx->loop_window();
// 	return (0);
// }