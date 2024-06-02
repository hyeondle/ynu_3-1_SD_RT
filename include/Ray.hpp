#ifndef RAY_HPP
#define RAY_HPP

#include "./Vector.hpp"

class ray {
	public:
		ray();
		ray(const point &origin, const vector &direction);

		point origin() const;
		vector direction() const;
		point at(double t) const;

	private:
		point orig;
		vector dir;
};

#endif