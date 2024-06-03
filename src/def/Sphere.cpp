#include "../../include/Sphere.hpp"

bool sphere::hit(const ray &r, interval ray_t, hit_record &rec) const{
	vector oc = center - r.origin();
	auto a = r.direction().length_squared();
	auto h = dot(r.direction(), oc);
	auto c = oc.length_squared() - radius*radius;

	auto discriminant = h*h - a*c;

	if (discriminant < 0) {
		return false;
	}

	auto sqrtd = sqrt(discriminant);

	//find the nearest root that lies in the acceptable range
	auto root = (h - sqrtd) / a;
	if (!ray_t.surrounds(root)) {
		root = (h + sqrtd) /a;
		if (!ray_t.surrounds(root)) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vector outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);

	return true;
}