#-------------------------------------------------------------------------------
# file:
#   http.cmake
# brief:
#   builds the module hryky-http by CMake
# version:
#   $Id: http.cmake 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
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
hryky_use_boost(asio)

set(KMYACC_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/include/hryky/http)

hryky_make_directory(${KMYACC_BINARY_DIR})

hryky_concat_file(
	${KMYACC_BINARY_DIR}/http_header.y
	kmyacc/http.declaration.y
	kmyacc/http.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ascii/kmyacc/ascii.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/date/kmyacc/date.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/uri/kmyacc/uri.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/uri/kmyacc/uri_common.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/uri/kmyacc/uri_authority.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_v4.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_v6.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/ip/kmyacc/ip_vf.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/core/kmyacc/base64.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/core/kmyacc/imf.rule.y
	${HRYKY_CODEBASE_ROOT}/lib/core/kmyacc/abnf.rule.y
	kmyacc/http.program.y)

hryky_add_kmyacc_parser(
	${KMYACC_BINARY_DIR}/http_header.y
	${KMYACC_BINARY_DIR})

set_source_files_properties(
	src/http_header_parser.cpp
	PROPERTIES OBJECT_DEPENDS 
	${KMYACC_BINARY_DIR}/http_header.y.h)

hryky_use_module(atomic chrono date uri ip type ascii)
