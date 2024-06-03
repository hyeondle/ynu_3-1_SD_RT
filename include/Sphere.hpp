#ifndef SPHERE_HPP
# define SPHERE_HPP

#include "./RTSet.hpp"
#include "./HitRecord.hpp"

class sphere : public hittable {
	public :
		sphere(const point &center, double radius, shared_ptr<material> mat) : center(center), radius(fmax(0, radius)), mat(mat) {}
		bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

	private :
		point center;
		double radius;
		shared_ptr<material> mat;
};

#endif