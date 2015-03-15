#-------------------------------------------------------------------------------
# file:
#   doc-hryky-codebase.cmake
# brief:
#   builds document for hryky-codebase.
# version:
#   $Id: CMakeLists.txt 152 2013-02-11 08:40:41Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
project(doc_hryky_codebase)
get_filename_component(
	HRYKY_CODEBASE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)

include(${HRYKY_CODEBASE_ROOT}/etc/common.cmake)

hryky_init_project_variables()

file(GLOB_RECURSE headers ${HRYKY_CODEBASE_ROOT}/lib/*.h)
hryky_use_doxygen(headers)

