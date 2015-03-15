#-------------------------------------------------------------------------------
# file:
#   profiler.cmake
# brief:
#   builds the module hryky-profiler by CMake
# version:
#   $Id: profiler.cmake 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
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

hryky_build_header_module()

hryky_use_module(chrono clock)
