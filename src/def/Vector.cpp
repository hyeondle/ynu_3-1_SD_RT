#include "../../include/Vector.hpp"

Vector::Vector() {
	e[0] = 0;
	e[1] = 0;
	e[2] = 0;
}

Vector::Vector(double e0, double e1, double e2) {
	e[0] = e0;
	e[1] = e1;
	e[2] = e2;
}

double Vector::x() const {
	return e[0];
}

double Vector::y() const {
	return e[1];
}

double Vector::z() const {
	return e[2];
}

double Vector::operator[](int i) const {
	return e[i];
}

double& Vector::operator[](int i) {
	return e[i];
}

Vector Vector::operator-() const {
	return Vector(-e[0], -e[1], -e[2]);
}

Vector& Vector::operator+=(const Vector &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

Vector& Vector::operator*=(const double t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

Vector& Vector::operator/=(const double t) {
	return *this *= 1/t;
}

double Vector::length() const {
	return std::sqrt(length_squared());
}

double Vector::length_squared() const {
	return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}