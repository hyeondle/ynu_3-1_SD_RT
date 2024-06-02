#include "../../include/Ray.hpp"

ray::ray() {}
ray::ray(const point &origin, const vector &direction) : orig(origin), dir(direction) {}

point ray::origin() const {
	return orig;
}

vector ray::direction() const {
	return dir;
}

point ray::at(double t) const {
	return orig + t * dir;
}