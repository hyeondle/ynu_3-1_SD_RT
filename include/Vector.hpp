#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <iostream>

class Vector {
	public:
		double e[3];

		Vector();
		Vector(double e0, double e1, double e2);

		double x() const;
		double y() const;
		double z() const;

		double operator[](int i) const;
		double& operator[](int i);

		Vector operator-() const;
		Vector& operator+=(const Vector &v);
		Vector& operator*=(const double t);
		Vector& operator/=(const double t);
		double length() const;
		double length_squared() const;
};

using Point = Vector;

inline std::ostream& operator<<(std::ostream &out, const Vector &v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector operator+(const Vector &u, const Vector &v) {
	return Vector(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector operator-(const Vector &u, const Vector &v) {
	return Vector(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector operator*(const Vector &u, const Vector &v) {
	return Vector(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector operator*(double t, const Vector &v) {
	return Vector(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vector operator*(const Vector &v, double t) {
	return t * v;
}

inline Vector operator/(Vector v, double t) {
	return (1/t) * v;
}

inline double dot(const Vector &u, const Vector &v) {
	return u.e[0] * v.e[0]
		 + u.e[1] * v.e[1]
		 + u.e[2] * v.e[2];
}

inline Vector cross(const Vector &u, const Vector &v) {
	return Vector(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				  u.e[2] * v.e[0] - u.e[0] * v.e[2],
				  u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector unit_vector(Vector v) {
	return v / v.length();
}

#endif