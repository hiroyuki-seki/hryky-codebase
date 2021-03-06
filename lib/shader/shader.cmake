#-------------------------------------------------------------------------------
# file:
#   shader.cmake
# brief:
#   builds the module hryky-shader by CMake
# version:
#   $Id: shader.cmake 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
get_filename_component(module_name ${CMAKE_CURRENT_LIST_DIR} NAME)
if (TARGET hryky_${module_name})
    return()
endif()

project(hryky_${module_name})
get_filename_component(
	HRYKY_CODEBASE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../.. ABSOLUTE)
#-------------------------------------------------------------------------------
# definitions of macro and function
#-------------------------------------------------------------------------------
include(${HRYKY_CODEBASE_ROOT}/etc/common.cmake)

set(HRYKY_PCH_SOURCE src/${module_name}.cpp)

hryky_build_library()

if(MSVC)
	add_definitions(-Zm129)
endif()

