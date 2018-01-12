#include <iostream>
#include <random>
#include <sstream>
#include <thread>
#include <algorithm>

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
	template <typename OutputT, typename HitableT, typename RandomizerT>
	fvec3 color(
		OutputT & output,
		ray_type const & ray,
		HitableT const & hitable,
		RandomizerT & randomizer,
		uint32_t const depth);

	/// appends objects.
	template <typename ContainerT, typename RandomizerT >
	bool scene(ContainerT & dest, RandomizerT & randomizer);

} // namespace

int main (int argc, char * argv[])
{
	uint32_t const width = 200u;
	uint32_t const height = 100u;
	uint32_t const samples = 100u;

	auto const lookfrom = fvec3(3.0f, 3.0f, 2.0f);
	auto const lookat = fvec3(0.0f, 0.0f, -1.0f);
	auto const up = fvec3(0.0f, 1.0f, 0.0f);
	auto const vfov = hryky::rtiow::degree(20.0f);
	auto const aspect = static_cast<float>(width) / height;
	auto const aperture = 2.0f;
	auto const dist_to_focus = (lookfrom - lookat).length();

	::std::random_device rd;

	randomizer_type randomizer(rd());

	camera_type const camera(
		lookfrom,
		lookat,
		up,
		vfov,
		aspect,
		aperture,
		dist_to_focus);

	container_type world;
	(void)scene(world, randomizer);

	uint32_t const hardware_concurrency = ::std::max(
		1u, std::thread::hardware_concurrency());
	auto const units_size = (
		height / hardware_concurrency
		+ (0u != height % hardware_concurrency ? 1 : 0));

	typedef ::std::ostringstream output_type;
	typedef ::std::vector<output_type> outputs_type;
	outputs_type outputs;
	outputs.resize(hardware_concurrency);

	typedef ::std::thread thread_type;
	typedef ::std::vector<thread_type> threads_type;
	threads_type threads;

	uint32_t y_itr = 0u;
	::std::for_each(
		::std::begin(outputs),
		::std::end(outputs),
		[&threads,
		&y_itr,
		width,
		height,
		samples,
		units_size,
		&rd,
		&world,
		&camera](output_type & output) -> void {

		auto const y_end = ::std::min(height, y_itr + units_size);
		auto const seed = rd();
		threads.emplace_back([
			&output,
			y_itr,
			y_end,
			height,
			width,
			samples,
			seed,
			&world,
			&camera]() -> void {

			randomizer_type randomizer(seed);
			auto y = y_itr;
			for (; y_end != y; ++y) {

				uint32_t x = 0u;
				for (; width != x; ++x) {
#if RTIOW_DEBUG
					(output << "# (" << x << "," << y << ")" << ::std::endl);
#endif

					fvec3 fcolor;
					uint32_t sample = 0u;
					for (; samples != sample; ++sample) {
						auto const ratio_x
							= (static_cast<float>(x) + randomizer()) / width;
						auto const ratio_y
							= (static_cast<float>(height - (y + 1u))
								+ randomizer()) / height;
						ray_type const ray
							= camera.ray(ratio_x, ratio_y, randomizer);
						fcolor += color(output, ray, world, randomizer, 50u);
					}

					fcolor /= samples;
					fcolor = sqrt(fcolor);
					auto const icolor = ivec3(255.99f * fcolor);
					(output << icolor << std::endl);
				}
			}
		});

		y_itr = y_end;
	});

	(::std::cout
	<< "P3" << ::std::endl
	<< width << " " << height << ::std::endl
	<< 255 << ::std::endl
	);

	::std::for_each(
		::std::begin(threads),
		::std::end(threads),
		[](thread_type & thread) -> void {
			thread.join();
		});

	::std::for_each(
		::std::begin(outputs),
		::std::end(outputs),
		[](output_type const & output) -> void {
			::std::cout << output.str();
		});

	return 0;
}

namespace
{
/**
  @brief retrieves the color at the position where a ray intersects the screen.
 */
template <typename OutputT, typename HitableT, typename RandomizerT>
fvec3 color(
	OutputT & output,
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
				(output << "# stopped:"
				 << "{depth:" << depth
				 << ",hit:" << hit
				 << "}" << std::endl);
#endif
				return fvec3();
			}
#if RTIOW_DEBUG
			(output << "# hit:"
			 << "{depth:" << depth
			 << ",hit:" << hit
			 << "}" << std::endl);
#endif
			return hit.scatter().attenuation() * color(
				output,
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

/**
  @brief appends objects.
 */
template <typename ContainerT, typename RandomizerT >
bool
scene(ContainerT & dest, RandomizerT & randomizer)
{
	dest.get().emplace_back(new sphere_type(
		fvec3(0.0f, -1000.0f, 0.0f),
		1000.0f,
		::std::make_shared<lambertian_type>(fvec3(0.5f, 0.5f, 0.5f))));

	auto x = -11;
	for (; 11 > x; ++x) {
		auto z = -11;
		for (; 11 > z; ++z) {
			fvec3 const center(
				x + 0.9f * randomizer(),
				0.2f,
				z + 0.9f * randomizer());
			if (0.9f >= (center - fvec3(4.0f, 0.2f, 0.0f)).length()) {
				continue;
			}

			auto const material = randomizer();
			if (0.8f > material) { // diffuse.
				dest.get().emplace_back(new sphere_type(
					center,
					0.2f,
					::std::make_shared<lambertian_type>(
						fvec3(
							randomizer() * randomizer(),
							randomizer() * randomizer(),
							randomizer() * randomizer()))));
			}
			else if (0.95f > material) { // metal
				dest.get().emplace_back(new sphere_type(
					center,
					0.2f,
					::std::make_shared<metal_type>(
						fvec3(
							0.5f * (1.0f + randomizer()),
							0.5f * (1.0f + randomizer()),
							0.5f * (1.0f + randomizer())),
						0.5f * randomizer())));
			}
			else { // glass
				dest.get().emplace_back(new sphere_type(
					center,
					0.2f,
					::std::make_shared<dielectric_type>(
						fvec3(1.0f, 1.0f, 1.0f),
						1.5f)));
			}
		}
	}

	dest.get().emplace_back(new sphere_type(
		fvec3(0.0f, 1.0f, 0.0f),
		1.0f,
		::std::make_shared<dielectric_type>(
			fvec3(1.0f, 1.0f, 1.0f),
			1.5f)));
	dest.get().emplace_back(new sphere_type(
		fvec3(-4.0f, 1.0f, 0.0f),
		1.0f,
		::std::make_shared<lambertian_type>(
			fvec3(0.4f, 0.2f, 0.1f))));
	dest.get().emplace_back(new sphere_type(
		fvec3(4.0f, 1.0f, 0.0f),
		1.0f,
		::std::make_shared<metal_type>(
			fvec3(0.7f, 0.6f, 0.5f),
			0.0f)));

	return true;
}

} // namespace

