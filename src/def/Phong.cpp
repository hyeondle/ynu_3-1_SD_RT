#include "Phong.hpp"
#include "Material.hpp"

const color phong::phong_lighting(const hit_record &rec, const ray &r, const hittable &world, const light& lights, const vector& ambient) {
	color light_color(0, 0, 0);

	light_color += phong_light_get(rec, r, lights, world);

	light_color += ambient;

	color albedo = rec.mat->g_albedo();

	// return (light_color * (albedo / 255.999));
	return light_color;
}

color phong::phong_light_get(const hit_record &rec, const ray &r, const light &lights, const hittable &world) {
	light_direction = lights.center - rec.p;
	light_length = light_direction.length();
	light_ray = ray(rec.p + rec.normal * EPSILON, light_direction);

	if (in_shadow(world, light_ray, light_length)) {
		return vector(0, 0, 0);
	}

	light_direction = unit(light_direction);
	kd = std::max(dot(rec.normal, light_direction), 0.0);
	diffuse = lights.color * kd;

	view_direction = unit(-r.direction());
	reflect_direction = reflect(-light_direction, rec.normal);
	spec = pow(std::max(dot(view_direction, reflect_direction), 0.0), ksn);
	specular = lights.color * ks * spec;
	brightness = lights.brightness * LUMEN;

	return color((diffuse + specular) * brightness);
}

vector phong::reflect(const vector &v, const vector &n) {
	return v - n * dot(v, n) * 2;
}

bool phong::in_shadow(const hittable &world, const ray &light_ray, double light_length) {
	hit_record temp_rec;
	interval shadow_interval(0, light_length);
	if (world.hit(light_ray, shadow_interval, temp_rec)) {
		return true;
	}
	return false;
}
