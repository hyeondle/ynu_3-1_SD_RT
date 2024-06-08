// #include "./minilibx/mlx.h"
#include "../include/RTSet.hpp"

#include "../include/BVH.hpp"
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

int SAMPLES_PER_PIXEL = 0;
int MAX_DEPTH = 0;
double GAMMA_REFLECTANCE = 0.0;

int main()
{
	int flag = 2;
	SAMPLES_PER_PIXEL = 1;
	MAX_DEPTH = 5;
	GAMMA_REFLECTANCE = 0.2;

	Mlx *mlx = new Mlx();

	// world
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

			if ((center - point(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else if (choose_mat < 0.95) {
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point(4, 1, 0), 1.0, material3));

	world = hittable_list(make_shared<bvh_node>(world));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = WIDTH;
	cam.samples_per_pixel = SAMPLES_PER_PIXEL;
	cam.max_depth = MAX_DEPTH;

	cam.vfov = 20;
	cam.lookfrom = point(13,2,3);
	cam.lookat = point(0,0,0);
	cam.vup = vector(0,1,0);

	auto light(1,1,1);

	if (flag == 1)
		cam.render(world, mlx);
	else if (flag == 2)
		cam.render(world, mlx, light);

	mlx->key_hook(mlx, cam, world);
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