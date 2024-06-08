#ifndef PHONG_HPP
#define PHONG_HPP

#include "RTSet.hpp"
#include "Light.hpp"

class phong {
public:
	vector diffuse;
	vector specular;
	vector light_direction;
	double kd;
	double light_length;
	ray light_ray;
	vector view_direction;
	vector reflect_direction;
	double spec;
	double ksn = 64;
	double ks = 0.5;
	double brightness;

	const color phong_lighting(const hit_record &rec, const ray &r, const hittable &world, const light& lights, const vector& ambient);

private:
	color phong_light_get(const hit_record &rec, const ray &r, const light &lights, const hittable &world);
	vector reflect(const vector &v, const vector &n);
	bool in_shadow(const hittable &world, const ray &light_ray, double light_length);
};


#endif