#ifndef COLOR_HPP
#define COLOR_HPP

#include "./Vector.hpp"
#include "./Interval.hpp"

class Mlx;

class color : public vector {
	public:
		color();
		color(double red, double green, double blue);
		color(const vector &v);

		int pixel;
	public:
		int get_color(const vector &color);
		// void write_color(Mlx *mlx,const Vector &color, int x, int y);
};

void write_color(Mlx *mlx, const vector &color, int x, int y);

inline double linear_to_gamma(double linear_component) {
	if (linear_component > 0)
		return sqrt(linear_component);

	return 0;
}

#endif