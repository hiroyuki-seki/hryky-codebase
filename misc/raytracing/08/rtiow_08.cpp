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
#include "../rtiow_randomizer.h"
#include "../rtiow_lambertian.h"
#include "../rtiow_metal.h"

namespace
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	typedef hryky::rtiow::Ray<> ray_type;
	typedef hryky::rtiow::Camera<> camera_type;
	typedef hryky::rtiow::Randomizer<> randomizer_type;
	typedef hryky::rtiow::Lambertian<> lambertian_type;
	typedef hryky::rtiow::Metal<> metal_type;
	typedef hryky::rtiow::Sphere<lambertian_type> lambert_sphere_type;
	typedef hryky::rtiow::Sphere<metal_type> metal_sphere_type;

	/// retrieves the color at the position where a ray intersects the screen.
	template <typename HitableT, typename RandomizerT>
	fvec3 color(
		ray_type const & ray,
		HitableT const & hitable,
		RandomizerT & randomizer,
		uint32_t const depth);

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
		lambert_sphere_type(
			fvec3(0.0f, 0.0f, -1.0f),
			0.5f,
			lambertian_type(fvec3(0.8f, 0.3f, 0.3f))),
		lambert_sphere_type(
			fvec3(0.0f, -100.5f, -1.0f),
			100.0f,
			lambertian_type(fvec3(0.8f, 0.8f, 0.3f))),
		metal_sphere_type(
			fvec3(1.0f, 0.0f, -1.0f),
			0.5f,
			metal_type(fvec3(0.8f, 0.6f, 0.2f), 1.0f)),
		metal_sphere_type(
			fvec3(-1.0f, 0.0f, -1.0f),
			0.5f,
			metal_type(fvec3(0.8f, 0.8f, 0.8f), 0.3f))
		));

	::std::random_device rd;

	randomizer_type randomizer(rd());

	uint32_t y = 0u;
	for (; height != y; ++y) {
		uint32_t x = 0u;
		for (; width != x; ++x) {
			fvec3 fcolor;
			uint32_t sample = 0u;
			for (; samples != sample; ++sample) {
				auto const ratio_x
					= (static_cast<float>(x) + randomizer()) / width;
				auto const ratio_y
					= (static_cast<float>(height - (y + 1u)) + randomizer()) / height;
				ray_type const ray = camera.ray(ratio_x, ratio_y);
				fcolor += color(ray, world, randomizer, 50u);
			}
			fcolor /= samples;
			fcolor = sqrt(fcolor);
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
	RandomizerT & randomizer,
	uint32_t const depth)
{
	{
		auto const hit = hitable.hit(ray, randomizer);
		if (!hryky_is_null(hit)) {
			if (0 == depth || hryky_is_null(hit.scatter())) {
				return fvec3();
			}
			return hit.scatter().attenuation() * color(
				hit.scatter().ray(),
				hitable,
				randomizer,
				depth - 1u);
		}
	}
	
	auto const unit = normalize(ray.direction());
	auto const ratio = 0.5f * (unit[1] + 1.0f);
	auto const white = fvec3(1.0f);
	auto const blue = fvec3(0.5f, 0.7f, 1.0f);
	
	return (1.0f - ratio) * white + ratio * blue;
}
} // namespace

