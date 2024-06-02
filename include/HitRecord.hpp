#ifndef HITRECORD_HPP
# define HITRECORD_HPP

#include "./Ray.hpp"

class hit_record {
	public :
		point p;
		vector normal;
		double t;
		bool front_face;

		void set_face_normal(const ray &r, const vector &outward_normal);
};

class hittable {
	public :
		virtual ~hittable() = default;

		virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const = 0;
};

#endif