#ifndef RTSET_HPP
# define RTSET_HPP

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

extern int SAMPLES_PER_PIXEL;
extern int MAX_DEPTH;
extern double GAMMA_REFLECTANCE;

#define LUMEN 3
#define EPSILON 1e-6

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