#-------------------------------------------------------------------------------
# file:
#   hryky-codebase.cmake
# brief:
#   builds hryky-codebase by CMake
# version:
#   $Id: hryky-codebase.cmake 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
project(hryky_codebase)

if (NOT HRYKY_CODEBASE_ROOT)
	get_filename_component(
		HRYKY_CODEBASE_ROOT ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
endif()

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	set(HRYKY_CODEBASE_INSTALL TRUE)
	set(HRYKY_CODEBASE_EXPORT FALSE)
else()
	set(HRYKY_CODEBASE_INSTALL FALSE)
	set(HRYKY_CODEBASE_EXPORT TRUE)
endif()


#-------------------------------------------------------------------------------
# definitions of macro and function
#-------------------------------------------------------------------------------
include(${HRYKY_CODEBASE_ROOT}/etc/common.cmake)

hryky_print_var(HRYKY_CODEBASE_INSTALL)
hryky_print_var(HRYKY_CODEBASE_EXPORT)

hryky_init_project_variables()

hryky_print_behavioral_variables()
hryky_print_system_variables()
hryky_print_c_variables()
hryky_print_cxx_variables()
hryky_print_project_variables()

add_custom_target(
	${PROJECT_NAME} ALL
	COMMENT "The default project containing all libraries.")
	
hryky_use_boost(asio filesystem thread)
hryky_use_sdl()
hryky_use_gl()
hryky_use_protobuf()
hryky_use_v8()

hryky_use_cppcheck(${HRYKY_CODEBASE_ROOT}/lib)

add_subdirectory(tool/concat)

#---------------------------------------
# configures modules.
#---------------------------------------
add_subdirectory(lib)

#-------------------------------------------------------------------------------
# For the development of hryky-codebase
#-------------------------------------------------------------------------------
if (HRYKY_CODEBASE_INSTALL)
	#---------------------------------------
	# appends the target to generate documents.
	#---------------------------------------
	add_subdirectory(doc)

	#---------------------------------------
	# tests library
	#---------------------------------------
	include(etc/test.cmake)
	
	#---------------------------------------
	# install the project
	#---------------------------------------
	include(etc/install.cmake)
	
	#---------------------------------------
	# creates the installer
	#---------------------------------------
	include(etc/pack.cmake)
endif()

#---------------------------------------
# exports variables.
#---------------------------------------
if (HRYKY_CODEBASE_EXPORT)
	hryky_export_var(HRYKY_MODULE_INCLUDE_DIRS)
	hryky_export_var(HRYKY_LIBRARY_PROJECTS)
endif()
