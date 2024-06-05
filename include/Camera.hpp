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

		void render(const hittable &world, Mlx *mlx);
	private :
		//var
		int image_height;
		double pixel_samples_scale;
		point center;
		point pixel00_loc;
		vector pixel_delta_u;
		vector pixel_delta_v;
		vector u,v,w;

		void initialize();
		ray get_ray(int i, int j) const;
		vector sample_square() const;
		color ray_color(const ray &r, int depth, const hittable &world) const;
};

#endif