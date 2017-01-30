#include <iostream>
#include <random>

#define RTIOW_DEBUG (0)

#include "../rtiow_radian.h"
#include "../rtiow_degree.h"
#include "../rtiow_vec3.h"
#include "../rtiow_ray_half.h"
#include "../rtiow_hittable_sphere.h"
#include "../rtiow_hittable_container.h"
#include "../rtiow_camera.h"
#include "../rtiow_randomizer.h"
#include "../rtiow_material_lambertian.h"
#include "../rtiow_material_metal.h"
#include "../rtiow_material_dielectric.h"

namespace
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	typedef hryky::rtiow::ray::Half<> ray_type;
	typedef hryky::rtiow::Camera<> camera_type;
	typedef hryky::rtiow::Randomizer<> randomizer_type;
	typedef hryky::rtiow::material::Lambertian<> lambertian_type;
	typedef hryky::rtiow::material::Metal<> metal_type;
	typedef hryky::rtiow::material::Dielectric<> dielectric_type;
	typedef hryky::rtiow::hittable::Sphere<> sphere_type;
	typedef hryky::rtiow::hittable::Container<> container_type;

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

	float const aspect = static_cast<float>(width) / height;

	camera_type const camera(
		fvec3(-2.0f, 2.0f, 1.0f),
		fvec3(0.0f, 0.0f, -1.0f),
		fvec3(0.0f, 1.0f, 0.0f),
		hryky::rtiow::degree(90.0f),
		static_cast<float>(width) / height);

	container_type world;
	world.get().emplace_back(new sphere_type(
		fvec3(0.0f, 0.0f, -1.0f),
		0.5f,
		::std::make_shared<lambertian_type>(fvec3(0.1f, 0.2f, 0.5f))));
	world.get().emplace_back(new sphere_type(
		fvec3(0.0f, -100.5f, -1.0f),
		100.0f,
		::std::make_shared<lambertian_type>(fvec3(0.8f, 0.8f, 0.0f))));
	world.get().emplace_back(new sphere_type(
		fvec3(1.0f, 0.0f, -1.0f),
		0.5f,
		::std::make_shared<metal_type>(fvec3(0.8f, 0.6f, 0.2f), 1.0f)));
	world.get().emplace_back(new sphere_type(
		fvec3(-1.0f, 0.0f, -1.0f),
		0.5f,
		::std::make_shared<dielectric_type>(fvec3(1.0f, 1.0f, 1.0f), 1.5f)));
	world.get().emplace_back(new sphere_type(
			fvec3(-1.0f, 0.0f, -1.0f),
			-0.45f,
		::std::make_shared<dielectric_type>(fvec3(1.0f, 1.0f, 1.0f), 1.5f)));

	::std::random_device rd;

	randomizer_type randomizer(rd());

	uint32_t y = 0u;
	for (; height != y; ++y) {
		uint32_t x = 0u;
		for (; width != x; ++x) {
#if RTIOW_DEBUG
			(::std::cout << "# (" << x << "," << y << ")" << ::std::endl);
#endif
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
#if RTIOW_DEBUG
				(::std::cout << "# stopped:"
				 << "{depth:" << depth
				 << ",hit:" << hit
				 << "}" << std::endl);
#endif
				return fvec3();
			}
#if RTIOW_DEBUG
			(::std::cout << "# hit:"
			 << "{depth:" << depth
			 << ",hit:" << hit
			 << "}" << std::endl);
#endif
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

