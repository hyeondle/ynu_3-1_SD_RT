#ifndef HITRECORD_HPP
# define HITRECORD_HPP

#include "./Ray.hpp"

class hit_record {
	public :
		point p;
		vector normal;
		double t;
};

#endif