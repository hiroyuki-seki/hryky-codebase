#include <iostream>
#include <random>

#include "../rtiow_vec3.h"
#include "../rtiow_hittable_sphere.h"
#include "../rtiow_hittable_container.h"
#include "../rtiow_camera.h"

namespace
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	typedef hryky::rtiow::ray::Half<> ray_type;
	typedef hryky::rtiow::hittable::Sphere<> sphere_type;
	typedef hryky::rtiow::hittable::Container<> container_type;
	typedef hryky::rtiow::Camera<> camera_type;

	/// retrieves the color at the position where a ray intersects the screen.
	template <typename HitableT>
	fvec3 color(ray_type const & ray, HitableT const & hitable);

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

	container_type world;
	world.get().emplace_back(new sphere_type(fvec3(0.0f, 0.0f, -1.0f), 0.5f));
	world.get().emplace_back(new sphere_type(fvec3(0.0f, -100.5f, -1.0f), 100.0f));

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
				fcolor += color(ray, world);
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

