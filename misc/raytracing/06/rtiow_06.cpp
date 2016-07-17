#include <iostream>

#include "../rtiow_vec3.h"
#include "../rtiow_ray.h"
#include "../rtiow_greater.h"
#include "../rtiow_less.h"
#include "../rtiow_has_verify.h"
#include "../rtiow_sphere.h"
#include "../rtiow_tuple.h"

namespace
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	typedef hryky::rtiow::Ray<> ray_type;
	typedef hryky::rtiow::Sphere<> sphere_type;

	/// retrieves the color at the position where a ray intersects the screen.
	template <typename HitableT>
	fvec3 color(ray_type const & ray, HitableT const & hitable);

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

	auto const world = hryky::rtiow::tuple(hryky::make_tuple(
		sphere_type(fvec3(0.0f, 0.0f, -1.0f), 0.5f),
		sphere_type(fvec3(0.0f, -100.5f, -1.0f), 100.0f)));

	uint32_t y = 0u;
	for (; height != y; ++y) {
		auto const ratio_y
			= static_cast<float>(height - (y + 1u)) / height;
		uint32_t x = 0u;
		for (; width != x; ++x) {
			auto const ratio_x
				= static_cast<float>(x) / width;
			ray_type const ray(
				origin,
				lower_left
				+ ratio_x * horizontal
				+ ratio_y * vertical);
			auto const fcolor = color(ray, world);
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
template <typename HitableT>
fvec3 color(ray_type const & ray, HitableT const & hitable)
{
	{
		auto const hit = hitable.hit(ray);
		if (!hryky_is_null(hit)) {
			return 0.5f * (hit.normal() + 1.0f);
		}
	}
	
	auto const unit = normalize(ray.direction());
	auto const ratio = 0.5f * (unit[1] + 1.0f);
	auto const white = fvec3(1.0f);
	auto const blue = fvec3(0.5f, 0.7f, 1.0f);
	
	return (1.0f - ratio) * white + ratio * blue;
}
} // namespace

