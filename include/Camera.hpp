#ifndef CAMERA_H
#define CAMERA_H

#include "RTSet.hpp"
#include "HitRecord.hpp"

#include "MlxBase.hpp"

class camera {
	public :
		//param
		double aspect_ratio = 1.0;
		int image_width = 720;
		int samples_per_pixel = 10;

		void render(const hittable &world, Mlx *mlx) {
			initialize();
			for (int j = 0; j < image_height; j++) {
				for (int i = 0; i < image_width; i++)
				{
					color pixel_color(0, 0, 0);
					for (int sample = 0; sample < samples_per_pixel; sample++) {
						ray r = get_ray(i, j);
						pixel_color += ray_color(r, world);
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

		void initialize() {
			image_height = int(image_width / aspect_ratio);
			image_height = (image_height < 1) ? 1 : image_height;

			pixel_samples_scale = 1.0 / samples_per_pixel;

			center = point(0, 0, 0);

			auto focal_length = 1.0;
			auto viewport_height = 2.0;
			auto viewport_width = viewport_height * (double(image_width) / image_height);

			auto viewport_u = vector(viewport_width, 0, 0);
			auto viewport_v = vector(0, -viewport_height, 0);

			pixel_delta_u = viewport_u / double(image_width);
			pixel_delta_v = viewport_v / double(image_height);

			auto viewport_upper_left = center - vector(0,0,focal_length) - viewport_u/2 - viewport_v/2;
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

		color ray_color(const ray &r, const hittable &world) const {
			hit_record rec;
			if (world.hit(r, interval(0, infinity), rec)) {
				return 0.5 * (rec.normal + color(1, 1, 1));
			}
			vector unit_direction = unit(r.direction());
			double t = 0.5 * (unit_direction.y() + 1.0);
			return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
		}
};

#endif