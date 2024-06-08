#include "Cylinder.hpp"

cylinder::cylinder(const point &center, vector &axis, double radius, double height, shared_ptr<material> mat) : center(center), axis(axis), radius(radius), height(height), mat(mat) {
	auto half_height = height / 2;
	auto half_radius = radius / 2;
	auto min = point(center.x() - half_radius, center.y() - half_height, center.z() - half_radius);
	auto max = point(center.x() + half_radius, center.y() + half_height, center.z() + half_radius);
	bbox = aabb(min, max);
}

bool cylinder::hit(const ray &r, interval ray_t, hit_record &rec) const {
    vector oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction()) - pow(dot(r.direction(), axis), 2);
    auto b = 2 * (dot(r.direction(), oc) - dot(r.direction(), axis) * dot(oc, axis));
    auto c = dot(oc, oc) - pow(dot(oc, axis), 2) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    auto top_centroid = center + axis * height;

    if (discriminant < 0) return false;

    auto sqrt_discriminant = sqrt(discriminant);
    auto t1 = (-b - sqrt_discriminant) / (2 * a);
    auto t2 = (-b + sqrt_discriminant) / (2 * a);

    bool hit = false;
    double t_hit = ray_t.max;

    auto check_cylinder_body = [&](double t) {
        if (t < ray_t.min || t > ray_t.max) return false;
        auto y = dot(r.at(t) - center, axis);
        return y > 0 && y < height;
    };

    if (check_cylinder_body(t1)) {
        hit = true;
        t_hit = t1;
    }
    if (check_cylinder_body(t2) && t2 < t_hit) {
        hit = true;
        t_hit = t2;
    }

    auto hit_caps = [&](const vector& cap_center) {
        vector oc = cap_center - r.origin();
        double t = dot(oc, axis) / dot(r.direction(), axis);
        if (t < ray_t.min || t > ray_t.max) return false;
        vector point_on_cap = r.at(t);
        vector d = point_on_cap - cap_center;
        d = d - axis * dot(d, axis); // Project onto plane
        return dot(d, d) <= radius * radius;
    };

    bool cap_hit = false;
    if (!hit) {
        if (hit_caps(center)) {
            t_hit = dot(center - r.origin(), axis) / dot(r.direction(), axis);
            cap_hit = true;
            hit = true;
        } else if (hit_caps(top_centroid)) {
            t_hit = dot(top_centroid - r.origin(), axis) / dot(r.direction(), axis);
            cap_hit = true;
            hit = true;
        }
    }

    if (!hit) return false;

    rec.t = t_hit;
    rec.p = r.at(t_hit);
    if (cap_hit) {
        vector outward_normal = (rec.p - (t_hit == t_hit ? center : top_centroid)) / radius;
        rec.set_face_normal(r, outward_normal);
    } else {
        vector op = rec.p - center;
        rec.normal = unit(op - axis * dot(op, axis));
        rec.set_face_normal(r, rec.normal);
    }
    rec.mat = mat;
    return true;
}
