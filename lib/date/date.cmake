#-------------------------------------------------------------------------------
# file:
#   date.cmake
# brief:
#   builds the module hryky-date by CMake
# version:
#   $Id: date.cmake 361 2014-07-06 10:03:06Z hryky.private@gmail.com $
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

# sets up the usage of Kmyacc.
set(KMYACC_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/hryky/date)
hryky_make_directory(${KMYACC_BINARY_DIR})
hryky_concat_file(
	${KMYACC_BINARY_DIR}/date.y
	kmyacc/date.declaration.y
	kmyacc/date.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	kmyacc/date.program.y)
hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/date.y
	${KMYACC_BINARY_DIR})
set_source_files_properties(
	src/date_parser.cpp
	PROPERTIES OBJECT_DEPENDS ${KMYACC_BINARY_DIR}/date.y.h)
	
hryky_use_module(ascii type)
