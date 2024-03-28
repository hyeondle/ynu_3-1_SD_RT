#include "../../include/Ray.hpp"

Ray::Ray() {}
Ray::Ray(const Point &origin, const Vector &direction) : orig(origin), dir(direction) {}

Point Ray::origin() const {
	return orig;
}

Vector Ray::direction() const {
	return dir;
}

Point Ray::at(double t) const {
	return orig + t * dir;
}