#include "Phong.hpp"

vector phong::phong_lighting(const hit_record &rec, const ray &r, const hittable &world, const std::vector<light>& lights, const vector& ambient) {
	vector light_color(0, 0, 0);

	for (const auto& light : lights) {
			light_color += phong_light_get(rec, r, light, world);
	}

	light_color += ambient;

	return min(light_color * (rec.albedo / 255.999), vector(1, 1, 1));
}

vector phong::phong_light_get(const hit_record &rec, const ray &r, const light &light, const hittable &world) {
	light_direction = light.position - rec.p;
	light_length = light_direction.length();
	light_ray = ray(rec.p + rec.normal * EPSILON, light_direction);

	if (in_shadow(world, light_ray, light_length)) {
		return vector(0, 0, 0);
	}

	light_direction = unit_vector(light_direction);
	kd = std::max(dot(rec.normal, light_direction), 0.0);
	diffuse = light.color * kd;

	view_direction = unit_vector(-r.direction());
	reflect_direction = reflect(-light_direction, rec.normal);
	spec = pow(std::max(dot(view_direction, reflect_direction), 0.0), ksn);
	specular = light.color * ks * spec;
	brightness = light.brightness * LUMEN;

	return (diffuse + specular) * brightness;
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
