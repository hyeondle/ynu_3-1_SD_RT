#ifndef HITLIST_HPP
# define HITLIST_HPP

#include "./RTSet.hpp"
#include "./HitRecord.hpp"

#include <vector>

class hittable_list : public hittable {
	public :
		std::vector< shared_ptr <hittable> > objects;

		hittable_list() {}
		hittable_list(shared_ptr<hittable> object);

		void clear();

		void add(shared_ptr<hittable> object);

		bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override;
};

#endif