#-------------------------------------------------------------------------------
# file:
#   socket.cmake
# brief:
#   builds the module hryky-socket by CMake
# version:
#   $Id: socket.cmake 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
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

hryky_use_openssl()

if (WIN32)
	hryky_use_module(win32)
endif()

