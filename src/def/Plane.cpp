#include "Plane.hpp"

plane::plane(const point &center, const vector &normal, shared_ptr<material> mat) : center(center), normal(normal), mat(mat) {}

bool plane::hit(const ray &r, interval ray_t, hit_record &rec) const {
    double denominator = dot(normal, r.direction());

    if (denominator > EPSILON || denominator < -EPSILON) {
        vector oc = center - r.origin();
        double t = dot(oc, normal) / denominator;

        if (t > ray_t.min && t < ray_t.max) {
            rec.t = t;
            rec.p = r.at(t);
            rec.normal = unit_vector(normal);
            rec.set_face_normal(r, rec.normal);
            rec.mat_ptr = mat;
            return true;
        }
    }
    return false;
}