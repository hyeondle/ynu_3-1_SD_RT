#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "RTSet.hpp"
#include "HitRecord.hpp"

class light : public hittable {
public:
	light(const point &center, const color &color, double brightness)
		: center(center), color(color), brightness(brightness) {}

	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		return false; // Lights don't interact with rays in this context
	}

	point center;
	color color;
	double brightness;
};

#endif