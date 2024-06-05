//Axis-Aligned Bounding Boxes

#ifndef AABB_HPP
#define AABB_HPP

#include "RTSet.hpp"

class aabb {
	public:
		interval x, y, z;

		aabb() {}

		aabb(const interval& x, const interval& y, const interval& z);
		aabb(const point& a, const point& b);
		aabb(const aabb& box0, const aabb& box1);

		const interval& axis_interval(int n) const;
		bool hit(const ray& r, interval ray_t) const;
		int longest_axis() const;

		static const aabb empty, universe;
};

#endif