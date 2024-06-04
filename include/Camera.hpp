#ifndef CAMERA_H
#define CAMERA_H

#include "RTSet.hpp"
#include "HitRecord.hpp"
#include "Material.hpp"
#include "MlxBase.hpp"

class camera {
	public :
		//param
		double aspect_ratio = 1.0;
		int image_width = 720;
		int samples_per_pixel = 10;
		int max_depth = 10;

		double vfov = 90;
		point lookfrom = point(0,0,0);
		point lookat = point(0,0,-1);
		vector vup = vector(0,1,0);

		void render(const hittable &world, Mlx *mlx) {
			initialize();
			for (int j = 0; j < HEIGHT; j++) {
				for (int i = 0; i < WIDTH; i++)
				{
					color pixel_color(0, 0, 0);
					for (int sample = 0; sample < samples_per_pixel; sample++) {
						ray r = get_ray(i, j);
						pixel_color += ray_color(r, max_depth, world);
					}
					// auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
					// auto ray_direction = pixel_center - center;
					// ray r(center, ray_direction);

					// color pixel_color = ray_color(r, world);
					write_color(mlx, pixel_samples_scale * pixel_color, i, j);
				}
			}
		}

	private :
		//var
		int image_height;
		double pixel_samples_scale;
		point center;
		point pixel00_loc;
		vector pixel_delta_u;
		vector pixel_delta_v;
		vector u,v,w;

		void initialize() {
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

		ray get_ray(int i, int j) const {
			auto offset = sample_square();
			auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

			auto ray_origin = center;
			auto ray_direction = pixel_sample - ray_origin;

			return ray(ray_origin, ray_direction);
		}

		vector sample_square() const {
			return vector(random_double() - 0.5, random_double() - 0.5, 0);
		}

		color ray_color(const ray &r, int depth, const hittable &world) const {
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
};

#endif