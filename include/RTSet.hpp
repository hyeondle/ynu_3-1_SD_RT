#ifndef RTSET_HPP
# define RTSET_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// c++ std using declarations
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constans
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

// common headers
#include "./Ray.hpp"
#include "./Vector.hpp"
#include "./Color.hpp"

#endif