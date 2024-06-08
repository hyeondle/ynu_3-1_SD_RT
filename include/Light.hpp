#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "RTSet.hpp"
#include "HitRecord.hpp"

class light : public hittable {
public:
	light(const point &center, const class color &color_, double brightness);

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