#ifndef PLANE_HPP
#define PLANE_HPP

#include "RTSet.hpp"
#include "HitRecord.hpp"

class plane : public hittable {
	public :
		plane(const point &center, const vector &normal, shared_ptr<material> mat);
		bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
	public :
		point center;
		vector normal;
		shared_ptr<material> mat;
};

#endif