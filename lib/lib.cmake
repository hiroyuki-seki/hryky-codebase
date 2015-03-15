#-------------------------------------------------------------------------------
# file:
#   lib.cmake
# brief:
#   builds all modules of hryky-codebase by CMake
# version:
#   $Id: lib.cmake 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
#
# output variables to parent scope:
#   HRYKY_MODULES is the list of the all names of module
#   HRYKY_LIBRARY_PROJECTS is the list of the all names of library project.
#-------------------------------------------------------------------------------
project(lib_hryky_codebase)

if (NOT HRYKY_CODEBASE_ROOT)
	get_filename_component(
		HRYKY_CODEBASE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
endif()

include(${HRYKY_CODEBASE_ROOT}/etc/common.cmake)

add_custom_target(${PROJECT_NAME})

hryky_init_project_variables()

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(HRYKY_CODEBASE_LIB_EXPORT FALSE)
else()
	set(HRYKY_CODEBASE_LIB_EXPORT TRUE)
endif()

foreach(module ${HRYKY_MODULES})
	if (TARGET hryky_${module})
		message(STATUS "hryky_${module} has been already configured.")
	else()
		add_subdirectory(${module})
		get_target_property(includes hryky_${module} INCLUDE_DIRECTORIES)
		list(APPEND HRYKY_MODULE_INCLUDE_DIRS ${includes})
		list(REMOVE_DUPLICATES HRYKY_MODULE_INCLUDE_DIRS)
	endif()
endforeach()

#-------------------------------------------------------------------------------
# exports variables.
#-------------------------------------------------------------------------------
if (HRYKY_CODEBASE_LIB_EXPORT)
	hryky_export_var(HRYKY_MODULES)
	hryky_export_var(HRYKY_LIBRARY_PROJECTS)
	hryky_export_var(HRYKY_MODULE_INCLUDE_DIRS)
endif()
