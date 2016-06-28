#include <iostream>

#include "../rtiow_vec3.h"

int main (int argc, char * argv[])
{
	typedef rtiow::Vec3<> vec3;
	
	uint32_t const width = 200u;
	uint32_t const height = 100u;
	
	(::std::cout
	 << "P3" << ::std::endl
	 << width << " " << height << ::std::endl
	 << 255 << ::std::endl);
	
	uint32_t y = 0u;
	for (; height != y; ++y) {
		uint32_t x = 0u;
		for (; width != x; ++x) {
			auto const fcolor = vec3(
				static_cast<float>(x) / width,
				static_cast<float>(height - (y + 1u)) / height,
				0.2f);
			auto const ired = static_cast<int32_t>(255.99f * fcolor[0]);
			auto const igreen = static_cast<int32_t>(255.99f * fcolor[1]);
			auto const iblue = static_cast<int32_t>(255.99f * fcolor[2]);
			(::std::cout
			 << ired << " " << igreen << " " << iblue << ::std::endl);
		}
	}
	return 0;
}
