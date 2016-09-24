cmake_minimum_required(VERSION 2.8.10.2)

project(zlib)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(
	../../../../zlib-1.2.5
	${CMAKE_CURRENT_BINARY_DIR}/zlib)

if (MSVC AND (CMAKE_SIZEOF_VOID_P EQUAL 8))
	set_target_properties(
		zlib PROPERTIES STATIC_LIBRARY_FLAGS "/MACHINE:x64")
endif()
