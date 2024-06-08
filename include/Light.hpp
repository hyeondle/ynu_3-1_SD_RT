#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "RTSet.hpp"
#include "HitRecord.hpp"

class light : public hittable {
public:
	light(const point &center, const color &color, double brightness)
		: center(center), color(color), brightness(brightness) {}

	bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
		return false;
	}

	aabb bounding_box() const override {
		return aabb(center, center);
	}

	point center;
	color color;
	double brightness;
};

#endif