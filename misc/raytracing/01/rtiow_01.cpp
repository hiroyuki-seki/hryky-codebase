#include <iostream>

#include "../rtiow_vec3.h"

int main (int argc, char * argv[])
{
	typedef hryky::rtiow::Vec3<> fvec3;
	typedef hryky::rtiow::Vec3<int32_t> ivec3;
	
	uint32_t const width = 200u;
	uint32_t const height = 100u;
	
	(::std::cout
	 << "P3" << ::std::endl
	 << width << " " << height << ::std::endl
	 << 255 << ::std::endl);
	
	uint32_t y = 0u;
	for (; height != y; ++y) {
		auto const ratio_y
			= static_cast<float>(height - (y + 1u)) / height;
		uint32_t x = 0u;
		for (; width != x; ++x) {
			auto const ratio_x = static_cast<float>(x) / width;
			auto const fcolor = fvec3(
				ratio_x,
				ratio_y,
				0.2f);
			auto const icolor = ivec3(255.99f * fcolor);
			(::std::cout << icolor << std::endl);
		}
	}
	return 0;
}
