#ifndef HITRECORD_HPP
# define HITRECORD_HPP

#include "./RTSet.hpp"

class material;

class hit_record {
	public :
		point p;
		vector normal;
		shared_ptr<material> mat;
		double t;
		bool front_face;

		void set_face_normal(const ray &r, const vector &outward_normal);
};

class hittable {
	public :
		virtual ~hittable() = default;

		virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif