#include "../../include/Color.hpp"
#include "../../include/MlxBase.hpp"

color::color() : vector() {}

color::color(double red, double green, double blue) : vector(red, green, blue) {}

color::color(const vector &v) : vector(v) {}

int color::get_color(const vector &color) {
	int ir = static_cast<int>(255.999 * color.x());
	int ig = static_cast<int>(255.999 * color.y());
	int ib = static_cast<int>(255.999 * color.z());
	pixel = (ir << 16) + (ig << 8) + ib;
	// pixel = (ib << 16) | (ig << 8) | ir;

	return (pixel);
}

void write_color(Mlx *mlx, const vector &color, int x, int y) {
	static const interval intensity(0.000, 0.999);
	int ir = static_cast<int>(256 * intensity.clamp(color.x()));
	int ig = static_cast<int>(256 * intensity.clamp(color.y()));
	int ib = static_cast<int>(256 * intensity.clamp(color.z()));
	int pixel = (ir << 16) + (ig << 8) + ib;
	// int pixel = (ib << 16) | (ig << 8) | ir;
	mlx->locate_pixel(x, y, pixel);
}