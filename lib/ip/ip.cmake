#-------------------------------------------------------------------------------
# file:
#   ip.cmake
# brief:
#   builds the module hryky-ip by CMake
# version:
#   $Id: ip.cmake 361 2014-07-06 10:03:06Z hryky.private@gmail.com $
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

set(KMYACC_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/hryky/ip)

hryky_make_directory(${KMYACC_BINARY_DIR})

# generates the parser for IPv4.
hryky_concat_file(
	${KMYACC_BINARY_DIR}/ip_v4.y
	kmyacc/ip_v4.declaration.y
	kmyacc/ip_v4.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	kmyacc/ip_v4.program.y)
hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/ip_v4.y
	${KMYACC_BINARY_DIR})
set_source_files_properties(
	src/ip_v4_entity.cpp
	PROPERTIES OBJECT_DEPENDS ${KMYACC_BINARY_DIR}/ip_v4.y.h)

# generates the parser for IPv6.
hryky_concat_file(
	${KMYACC_BINARY_DIR}/ip_v6.y
	kmyacc/ip_v6.declaration.y
	kmyacc/ip_v6.rule.y
	kmyacc/ip_v4.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	kmyacc/ip_v6.program.y)
hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/ip_v6.y
	${KMYACC_BINARY_DIR})
set_source_files_properties(
	src/ip_v6_entity.cpp
	PROPERTIES OBJECT_DEPENDS ${KMYACC_BINARY_DIR}/ip_v6.y.h)
	
# generates the parser for future IP Address.
hryky_concat_file(
	${KMYACC_BINARY_DIR}/ip_vf.y
	kmyacc/ip_vf.declaration.y
	kmyacc/ip_vf.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	kmyacc/ip_vf.program.y)
hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/ip_vf.y
	${KMYACC_BINARY_DIR})
set_source_files_properties(
	src/ip_vf_entity.cpp
	PROPERTIES OBJECT_DEPENDS ${KMYACC_BINARY_DIR}/ip_vf.y.h)
	
hryky_use_module(type ascii)
