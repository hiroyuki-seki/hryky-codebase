#-------------------------------------------------------------------------------
# file:
#   uri.cmake
# brief:
#   builds the module hryky-uri by CMake
# version:
#   $Id: uri.cmake 361 2014-07-06 10:03:06Z hryky.private@gmail.com $
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

set(KMYACC_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/hryky/uri)

hryky_make_directory(${KMYACC_BINARY_DIR})

# generates the parser for URI.
hryky_concat_file(
	${KMYACC_BINARY_DIR}/uri.y
	kmyacc/uri.declaration.y
	kmyacc/uri.rule.y
	kmyacc/uri_common.rule.y
	kmyacc/uri_authority.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_v4.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_v6.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_vf.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	kmyacc/uri.program.y)
hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/uri.y
	${KMYACC_BINARY_DIR})
set_source_files_properties(
	src/uri_parser.cpp
	PROPERTIES OBJECT_DEPENDS ${KMYACC_BINARY_DIR}/uri.y.h)
	
# generates the parser for the authority part of URI.
hryky_concat_file(
	${KMYACC_BINARY_DIR}/uri_authority.y
	kmyacc/uri_authority.declaration.y
	kmyacc/uri_common.rule.y
	kmyacc/uri_authority.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_v4.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_v6.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_vf.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	kmyacc/uri_authority.program.y)
hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/uri_authority.y
	${KMYACC_BINARY_DIR})
set_source_files_properties(
	src/uri_authority_parser.cpp
	PROPERTIES OBJECT_DEPENDS ${KMYACC_BINARY_DIR}/uri_authority.y.h)
	
hryky_use_module(ascii ip type)
