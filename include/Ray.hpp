#ifndef RAY_HPP
#define RAY_HPP

#include "./Vector.hpp"

class Ray {
	public:
		Ray();
		Ray(const Point &origin, const Vector &direction);

		Point origin() const;
		Vector direction() const;
		Point at(double t) const;

	private:
		Point orig;
		Vector dir;
};

#endif