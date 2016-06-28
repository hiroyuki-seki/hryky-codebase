#include <iostream>

#include "../vec3.h"

int main (int argc, char * argv[])
{
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
			auto const red = static_cast<float>(x) / width;
			auto const green = static_cast<float>(height - (y + 1u)) / height;
			auto const blue = 0.2f;
			auto const ired = static_cast<int32_t>(255.99f * red);
			auto const igreen = static_cast<int32_t>(255.99f * green);
			auto const iblue = static_cast<int32_t>(255.99f * blue);
			(::std::cout
			 << ired << " " << igreen << " " << iblue << ::std::endl);
		}
	}
	return 0;
}
