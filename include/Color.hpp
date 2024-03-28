#ifndef COLOR_HPP
#define COLOR_HPP

#include "./Vector.hpp"
#include <iostream>

class Mlx;

class Color : public Vector {
	public:
		Color();
		Color(double red, double green, double blue);
		Color(const Vector &v);

		int pixel;
	public:
		int get_color(const Vector &color);
		// void write_color(Mlx &mlx,const Vector &color, int x, int y);
};

void write_color(Mlx &mlx, const Vector &color, int x, int y);

#endif