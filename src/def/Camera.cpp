#include "Camera.hpp"
#include "Phong.hpp"

void camera::render(const hittable &world, Mlx *mlx) {
	initialize();
	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++)
		{
			color pixel_color(0, 0, 0);
			for (int sample = 0; sample < samples_per_pixel; sample++) {
				ray r = get_ray(i, j);
				pixel_color += ray_color(r, max_depth, world);
			}
			write_color(mlx, pixel_samples_scale * pixel_color, i, j);
		}
	}
	mlx->put_image_to_window();
}

void camera::render(const hittabel &world, Mlx *mlx, light light) {
	initialize();
	auto ambient(AMBIENT_R, AMBIENT_G, AMBIENT_B);

	for (int j = 0; j < HEIGHT; j++) {
		for (int i = 0; i < WIDTH; i++)
		{
			auto u = double(i) / (WIDTH - 1);
			auto v = double(j) / (HEIGHT - 1);
			ray r = get_ray(u, v);
			auto pixel_color = ray_color(r, world, light, ambient);
			write_color(mlx, pixel_color, i, j);
		}
	}
	mlx->put_image_to_window();
}

void camera::initialize() {
	image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	pixel_samples_scale = 1.0 / samples_per_pixel;

	center = lookfrom;

	auto focal_length = (lookfrom - lookat).length();
	auto theta = degrees_to_radians(vfov);
	auto h = tan(theta/2);
	auto viewport_height = 2 * h * focal_length;
	auto viewport_width = viewport_height * (double(image_width) / image_height);

	w = unit(lookfrom - lookat);
	u = unit(cross(vup, w));
	v = cross(w, u);

	auto viewport_u = viewport_width * u;
	auto viewport_v = viewport_height * -v;

	pixel_delta_u = viewport_u / double(image_width);
	pixel_delta_v = viewport_v / double(image_height);

	auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

ray camera::get_ray(int i, int j) const {
	auto offset = sample_square();
	auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

	auto ray_origin = center;
	auto ray_direction = pixel_sample - ray_origin;

	return ray(ray_origin, ray_direction);
}

vector camera::sample_square() const {
	return vector(random_double() - 0.5, random_double() - 0.5, 0);
}

color camera::ray_color(const ray &r, int depth, const hittable &world) const {
	if (depth <= 0)
		return color(0, 0, 0);

	hit_record rec;
	if (world.hit(r, interval(0.001, infinity), rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, depth-1, world);
			return color(0,0,0);
	}
	vector unit_direction = unit(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

color camera::ray_color(const ray &r, const hittable &world, light &light, vector ambient) const {
	hit_record rec;
	if (world.hit(r, interval(0.001, infinity), rec)) {
		return phong::phong_lighting(rec, r, world, light, ambient);
	}
	return color(0, 0, 0);
}

// camera movement and rotation

void camera::move_camera_x(double delta, hittable &world, Mlx *mlx) {
    lookfrom.e[0] += delta;
    lookat.e[0] += delta;
    render(world, mlx);
}

void camera::move_camera_y(double delta, hittable &world, Mlx *mlx) {
    lookfrom.e[1] += delta;
    lookat.e[1] += delta;
    render(world, mlx);
}

void camera::move_camera_z(double delta, hittable &world, Mlx *mlx) {
    lookfrom.e[2] += delta;
    lookat.e[2] += delta;
    render(world, mlx);
}

void camera::rotate_camera_yaw(double yaw, hittable &world, Mlx *mlx) {
    double cos_theta = cos(yaw);
    double sin_theta = sin(yaw);
    vector look_dir = lookat - lookfrom;
    look_dir = vector(
        cos_theta * look_dir.x() - sin_theta * look_dir.z(),
        look_dir.y(),
        sin_theta * look_dir.x() + cos_theta * look_dir.z()
    );
    lookat = lookfrom + look_dir;
    render(world, mlx);
}

void camera::rotate_camera_pitch(double pitch, hittable &world, Mlx *mlx) {
    double cos_theta = cos(pitch);
    double sin_theta = sin(pitch);
    vector look_dir = lookat - lookfrom;
    look_dir = vector(
        look_dir.x(),
        cos_theta * look_dir.y() - sin_theta * look_dir.z(),
        sin_theta * look_dir.y() + cos_theta * look_dir.z()
    );
    lookat = lookfrom + look_dir;
    render(world, mlx);
}

void camera::rotate_camera_roll(double roll, hittable &world, Mlx *mlx) {
	double cos_theta = cos(roll);
	double sin_theta = sin(roll);
	vector look_dir = lookat - lookfrom;
	look_dir = vector(
		cos_theta * look_dir.x() - sin_theta * look_dir.y(),
		sin_theta * look_dir.x() + cos_theta * look_dir.y(),
		look_dir.z()
	);
	lookat = lookfrom + look_dir;
	render(world, mlx);
}