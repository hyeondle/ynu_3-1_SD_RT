#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "RTSet.hpp"
#include "HitRecord.hpp"

class cylinder : public hittable {
	public :
		cylinder(const point &center, vector &axis, double radius, double height, shared_ptr<material> mat);
		bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
	public :
		point center;
		vector axis;
		double radius;
		double height;
		shared_ptr<material> mat;
		aabb bbox;
};

#endif