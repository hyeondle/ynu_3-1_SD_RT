#ifndef RTSET_HPP
# define RTSET_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#define SAMPLES_PER_PIXEL 50
#define MAX_DEPTH 5
#define GAMMA_REFLECTANCE 0.2

// c++ std using declarations
using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// common headers
#include "./Utils.hpp"
#include "./Ray.hpp"
#include "./Vector.hpp"
#include "./Color.hpp"
#include "./Interval.hpp"

#endif