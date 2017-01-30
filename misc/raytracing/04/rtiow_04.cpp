#include <iostream>

#include "../rtiow_vec3.h"
#include "../rtiow_ray_half.h"

namespace
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	typedef hryky::rtiow::ray::Half<> ray_type;

	/// retrieves the color at the position where a ray intersects the screen.
	fvec3 color(ray_type const & ray);

	/// confirms whether a ray intersects a sphere.
	float hit_sphere(fvec3 const & center, float const radius, ray_type const & ray);

} // namespace

int main (int argc, char * argv[])
{
	uint32_t const width = 200u;
	uint32_t const height = 100u;
	
	(::std::cout
	 << "P3" << ::std::endl
	 << width << " " << height << ::std::endl
	 << 255 << ::std::endl);

	fvec3 const origin(0.0f);
	fvec3 const lower_left(-2.0f, -1.0f, -1.0f);
	fvec3 const horizontal(4.0f, 0.0f, 0.0f);
	fvec3 const vertical(0.0f, 2.0f, 0.0f);
	
	uint32_t y = 0u;
	for (; height != y; ++y) {
		auto const ratio_y
			= static_cast<float>(height - (y + 1u)) / height;
		uint32_t x = 0u;
		for (; width != x; ++x) {
		auto const ratio_x
			= static_cast<float>(x) / width;
			auto const fcolor = color(ray_type(
				origin,
				lower_left
				+ ratio_x * horizontal
				+ ratio_y * vertical));
			auto const icolor = ivec3(255.99f * fcolor);
			(::std::cout << icolor << std::endl);
		}
	}
	return 0;
}

namespace
{
/**
  @brief retrieves the color at the position where a ray intersects the screen.
 */
fvec3 color(ray_type const & ray)
{
	{
		auto const center = fvec3(0.0f, 0.0f, -1.0f);
		auto const t = hit_sphere(center, 0.5f, ray);
		if (0.0f < t) {
			auto const hit = ray.point(t);
			auto const normal = normalize(hit - center);
			return 0.5f * (normal + 1.0f);
		}
	}
	
	auto const unit = normalize(ray.direction());
	auto const ratio = 0.5f * (unit[1] + 1.0f);
	auto const white = fvec3(1.0f);
	auto const blue = fvec3(0.5f, 0.7f, 1.0f);
	
	return (1.0f - ratio) * white + ratio * blue;
}
/**
  @brief confirms whether a ray intersects a sphere.
 */
float hit_sphere(fvec3 const & center, float const radius, ray_type const & ray)
{
	auto const oc = ray.origin() - center;
	auto const a = dot(ray.direction(), ray.direction());
	auto const b = 2.0f * dot(ray.direction(), oc);
	auto const c = dot(oc, oc) - radius * radius;
	auto const discriminant = b * b - 4.0f * a * c;

	if (0.0f > discriminant) {
		return -1.0f;
	}

	return (-b - ::std::sqrt(discriminant)) / (2.0f * a);
}
} // namespace

