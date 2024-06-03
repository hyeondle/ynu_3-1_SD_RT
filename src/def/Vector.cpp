#include "../../include/Vector.hpp"

vector::vector() {
	e[0] = 0;
	e[1] = 0;
	e[2] = 0;
}

vector::vector(double e0, double e1, double e2) {
	e[0] = e0;
	e[1] = e1;
	e[2] = e2;
}

double vector::x() const {
	return e[0];
}

double vector::y() const {
	return e[1];
}

double vector::z() const {
	return e[2];
}

double vector::operator[](int i) const {
	return e[i];
}

double& vector::operator[](int i) {
	return e[i];
}

vector vector::operator-() const {
	return vector(-e[0], -e[1], -e[2]);
}

vector& vector::operator+=(const vector &v) {
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

vector& vector::operator*=(const double t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

vector& vector::operator/=(const double t) {
	return *this *= 1/t;
}

double vector::length() const {
	return std::sqrt(length_squared());
}

double vector::length_squared() const {
	return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

vector vector::random() {
	return vector(random_double(), random_double(), random_double());
}

vector vector::random(double min, double max) {
	return vector(random_double(min, max), random_double(min, max), random_double(min, max));
}