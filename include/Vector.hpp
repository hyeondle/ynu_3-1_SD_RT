#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <./Utils.hpp>

class vector {
	public:
		double e[3];

		vector();
		vector(double e0, double e1, double e2);

		double x() const;
		double y() const;
		double z() const;

		double operator[](int i) const;
		double& operator[](int i);

		vector operator-() const;
		vector& operator+=(const vector &v);
		vector& operator*=(const double t);
		vector& operator/=(const double t);
		double length() const;
		double length_squared() const;
		bool near_zero() const;

		static vector random();
		static vector random(double min, double max);
};

using point = vector;

inline std::ostream& operator<<(std::ostream &out, const vector &v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector operator+(const vector &u, const vector &v) {
	return vector(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vector operator-(const vector &u, const vector &v) {
	return vector(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector operator*(const vector &u, const vector &v) {
	return vector(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector operator*(double t, const vector &v) {
	return vector(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vector operator*(const vector &v, double t) {
	return t * v;
}

inline vector operator/(vector v, double t) {
	return (1/t) * v;
}

inline double dot(const vector &u, const vector &v) {
	return u.e[0] * v.e[0]
		 + u.e[1] * v.e[1]
		 + u.e[2] * v.e[2];
}

inline vector cross(const vector &u, const vector &v) {
	return vector(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				  u.e[2] * v.e[0] - u.e[0] * v.e[2],
				  u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector unit(vector v) {
	return v / v.length();
}

inline vector random_in_unit_sphere() {
	while (true) {
		auto p = vector::random(-1, 1);
		if (p.length_squared() < 1)
			return p;
	}
}

inline vector random_unit_vector() {
	return unit(random_in_unit_sphere());
}

inline vector random_on_hemisphere(const vector &normal) {
	vector on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0)
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

inline vector reflect(const vector &v, const vector &n) {
	return v - 2 * dot(v,n) * n;
}

inline vector refract(const vector &uv, const vector &n, double etai_over_etat) {
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vector r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vector r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

#endif