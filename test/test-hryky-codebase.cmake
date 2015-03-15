#-------------------------------------------------------------------------------
# file:
#   test-hryky-codebase.cmake
# brief:
#   builds the testing executable for hryky-codebase by CMake
# version:
#   $Id: test-hryky-codebase.cmake 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
project(test_hryky_codebase)
get_filename_component(
	HRYKY_CODEBASE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)

#-------------------------------------------------------------------------------
# definitions of macro and function
#-------------------------------------------------------------------------------
include(${HRYKY_CODEBASE_ROOT}/etc/common.cmake)

set(HRYKY_PCH_SOURCE src/common/test.cpp)
set(HRYKY_MODULE_BINARY_ROOT ${CMAKE_CURRENT_BINARY_DIR}/../lib)

math(EXPR HRYKY_TEST_MEMORY_SIZE "(1024 * 1024 * 512)")
add_definitions(-DHRYKY_TEST_MEMORY_SIZE=${HRYKY_TEST_MEMORY_SIZE})

hryky_build_executable()

set(HRYKY_TEST_BIGOBJ 0)
hryky_append_definitions(
	src/test_bitset.cpp HRYKY_TEST_BIGOBJ=${HRYKY_TEST_BIGOBJ})

if(MSVC AND HRYKY_TEST_BIGOBJ)
	set(ADDITIONAL_FLAGS /bigobj)
	hryky_append_compile_flags(src/test_bitset.cpp ADDITIONAL_FLAGS)
endif()

include_directories(src/common)

hryky_use_openssl()
hryky_use_module(${HRYKY_MODULES})
hryky_use_boost(asio thread)
hryky_use_sdl()
hryky_use_gl()
hryky_use_protobuf()
hryky_use_v8()
hryky_use_ipafont()
hryky_use_freeglut()
hryky_use_module(${HRYKY_MODULES})
