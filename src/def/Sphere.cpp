#include "../../include/Sphere.hpp"

sphere::sphere(const point &center, double radius, shared_ptr<material> mat) : center(center), radius(fmax(0, radius)), mat(mat) {
	auto rvec = vector(radius, radius, radius);
	bbox = aabb(center - rvec, center + rvec);
}

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
	rec.mat = mat;

	return true;
}

aabb sphere::bounding_box() const {
	return bbox;
}