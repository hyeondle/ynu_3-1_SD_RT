#include "../../include/Color.hpp"
#include "../../include/MlxBase.hpp"

Color::Color() : Vector() {}

Color::Color(double red, double green, double blue) : Vector(red, green, blue) {}

Color::Color(const Vector &v) : Vector(v) {}

int Color::get_color(const Vector &color) {
	int ir = static_cast<int>(255.999 * color.x());
	int ig = static_cast<int>(255.999 * color.y());
	int ib = static_cast<int>(255.999 * color.z());
	// pixel = (ir << 16) + (ig << 8) + ib;
	pixel = (ib << 16) | (ig << 8) | ir;

	return (pixel);
}

void write_color(Mlx &mlx, const Vector &color, int x, int y) {
	int ir = static_cast<int>(255.999 * color.x());
	int ig = static_cast<int>(255.999 * color.y());
	int ib = static_cast<int>(255.999 * color.z());
	int pixel = (ir << 16) + (ig << 8) + ib;
	// int pixel = (ib << 16) | (ig << 8) | ir;
	mlx.locate_pixel(x, y, pixel);
}