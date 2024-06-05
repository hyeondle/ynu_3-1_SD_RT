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
		bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
		aabb bounding_box() const override {return bbox;}
	private :
		aabb bbox;
};

#endif