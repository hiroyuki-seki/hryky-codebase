#include <iostream>
#include <random>

#include "../rtiow_vec3.h"
#include "../rtiow_ray.h"
#include "../rtiow_greater.h"
#include "../rtiow_less.h"
#include "../rtiow_has_verify.h"
#include "../rtiow_sphere.h"
#include "../rtiow_tuple.h"
#include "../rtiow_camera.h"

namespace
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	typedef hryky::rtiow::Ray<> ray_type;
	typedef hryky::rtiow::Sphere<> sphere_type;
	typedef hryky::rtiow::Camera<> camera_type;

	/// retrieves the color at the position where a ray intersects the screen.
	template <typename HitableT, typename RandomizerT>
	fvec3 color(
		ray_type const & ray,
		HitableT const & hitable,
		RandomizerT randomizer);

	/// generates a point in a unit sphere.
	template <typename RandomizerT>
	fvec3 in_sphere(RandomizerT randomizer);

} // namespace

int main (int argc, char * argv[])
{
	uint32_t const width = 200u;
	uint32_t const height = 100u;
	uint32_t const samples = 100u;
	
	(::std::cout
	 << "P3" << ::std::endl
	 << width << " " << height << ::std::endl
	 << 255 << ::std::endl);

	camera_type const camera;

	auto const world = hryky::rtiow::tuple(hryky::make_tuple(
		sphere_type(fvec3(0.0f, 0.0f, -1.0f), 0.5f),
		sphere_type(fvec3(0.0f, -100.5f, -1.0f), 100.0f)));

	::std::random_device rd;
	::std::mt19937 gen(rd());
	::std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	uint32_t y = 0u;
	for (; height != y; ++y) {
		uint32_t x = 0u;
		for (; width != x; ++x) {
			fvec3 fcolor;
			uint32_t sample = 0u;
			for (; samples != sample; ++sample) {
				auto const ratio_x
					= (static_cast<float>(x) + dist(gen)) / width;
				auto const ratio_y
					= (static_cast<float>(height - (y + 1u)) + dist(gen)) / height;
				ray_type const ray = camera.ray(ratio_x, ratio_y);
				fcolor += color(ray, world, [&gen, &dist]() { return dist(gen); });
			}
			fcolor /= samples;
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
template <typename HitableT, typename RandomizerT>
fvec3 color(
	ray_type const & ray,
	HitableT const & hitable,
	RandomizerT randomizer)
{
	{
		auto const hit = hitable.hit(ray);
		if (!hryky_is_null(hit)) {
			auto const target = hit.pos() + hit.normal() + in_sphere(randomizer);
			return 0.5f * color(
				ray_type(hit.pos(), target - hit.pos()),
				hitable,
				randomizer);
		}
	}
	
	auto const unit = normalize(ray.direction());
	auto const ratio = 0.5f * (unit[1] + 1.0f);
	auto const white = fvec3(1.0f);
	auto const blue = fvec3(0.5f, 0.7f, 1.0f);
	
	return (1.0f - ratio) * white + ratio * blue;
}
/**
  @brief generates a point on a unit sphere.
 */
template <typename RandomizerT>
fvec3 in_sphere(RandomizerT randomizer)
{
	fvec3 p;
	do {
		p = 2.0f * fvec3(randomizer(), randomizer(), randomizer()) - 1.0f;
	} while (p.slength() >= 1.0f);
	return p;
}
} // namespace

