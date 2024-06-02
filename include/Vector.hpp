#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <iostream>

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

#endif