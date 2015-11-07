#-------------------------------------------------------------------------------
# file:
#   common.cmake
# brief:
#   common definitions for CMake
# version:
#   $Id: common.cmake 380 2014-08-24 07:41:16Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
if (NOT DEFINED HRYKY_CODEBASE_ROOT)
	message(FATAL_ERROR "The variable HRYKY_CODEBASE_ROOT has to be defined.")
	return()
endif()

if (hryky_common_cmake_included)
	return()
endif()
set(hryky_common_cmake_included true)

#-------------------------------------------------------------------------------
# functions
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# appends a library to be built.
# param : {string} name is the name of the project.
# param : {ARGN} The optional arguments are source files.
#-------------------------------------------------------------------------------
function(hryky_append_built_library name)
	list(LENGTH ARGN sources_length)
	if (NOT sources_length)
		return()
	endif()

	hryky_debug("appends ${name} as library")
	hryky_debug("library sources : ${ARGN}")

	if (HRYKY_BUILD_STATIC_LIB)
		add_library(${name} STATIC ${ARGN})
	else()
		add_library(${name} SHARED ${ARGN})
	endif()
	
endfunction()

#-------------------------------------------------------------------------------
# installs a directory
# param : src is the path to the source directory.
# param : dest is the path to the destination directory.
#-------------------------------------------------------------------------------
function(hryky_install_directory src dest)
	get_filename_component(src ${src} ABSOLUTE)
	if (NOT EXISTS ${src})
		return()
	endif()
	
	hryky_debug("installs ${src} to ${dest}")
	
	install(DIRECTORY ${src}
		DESTINATION ${dest}
		COMPONENT ${PROJECT_NAME}
		PATTERN ".svn" EXCLUDE
		PATTERN "XTAGS" EXCLUDE
		PATTERN "precompiled.h" EXCLUDE
		PATTERN "*.h")
endfunction()

#------------------------------------------------------------------------------
# appends linked libraries to the current target.
# param : {ARGV} The optional arguments are the list of the additional libraries.
#------------------------------------------------------------------------------
function(hryky_link_libraries)
	get_target_property(project_type ${PROJECT_NAME} TYPE)
	if (NOT 
		((EXECUTABLE STREQUAL ${project_type}) OR 
		(SHARED_LIBRARY STREQUAL ${project_type})))
		return()
	endif()
	
	hryky_debug("${PROJECT_NAME} links: ${ARGV}")
	target_link_libraries(${PROJECT_NAME} ${ARGV})
endfunction()

#------------------------------------------------------------------------------
# appends a property of CMake directory scope.
# param : {string} name is the name of directory property.
# param : {string} value is the value of the directory property.
#------------------------------------------------------------------------------
function(hryky_append_directory_property name value)
	get_directory_property(VAR ${name})
	list(APPEND VAR ${value})
	set_directory_properties(PROPERTIES ${name} "${VAR}")
	hryky_debug("appends directory property ${name} : ${VAR}")
endfunction()

#-------------------------------------------------------------------------------
# confirms whether the list include the specified value.
# param : {variable} list_var is the variable of list.
# param : {string} value is searched in the value of list_var.
# param : {variable} is_found_var will contain the boolean result.
#-------------------------------------------------------------------------------
function(hryky_search list_var value is_found_var)
	list(FIND ${list_var} ${value} found_index)
	if (found_index LESS 0)
		set(${is_found_var} false)
	else()
		set(${is_found_var} true)
	endif()
	hryky_export_var_quietly(${is_found_var})
endfunction()

#-------------------------------------------------------------------------------
# uses other modules
# param : {ARGV} optional arguments are the list of modules.
#
# options: 
#   {path}  HRYKY_MODULE_BINARY_ROOT is the root of binary directories for 
#           sub modules. The default value is <CMAKE_CURRENT_BINARY_DIR>/..
#-------------------------------------------------------------------------------
function(hryky_use_module)
	set(modules ${ARGV})

	# returns if threre is no module.
	list(LENGTH modules modules_size)
	if (NOT modules_size)
		return()
	endif()

	string(REGEX REPLACE "hryky_" "" module_name ${PROJECT_NAME})
	list(REMOVE_ITEM modules ${module_name})
	
	hryky_debug("${PROJECT_NAME} starts to use ${modules} {")
	hryky_descend()
	
	if (NOT HRYKY_CODEBASE_ROOT)
		hryky_emerg("HRYKY_CODEBASE_ROOT is not defined.")
	endif()

	if (NOT DEFINED HRYKY_MODULE_BINARY_ROOT)
		get_filename_component(HRYKY_MODULE_BINARY_ROOT
			${CMAKE_CURRENT_BINARY_DIR}/.. ABSOLUTE)
	endif()

	hryky_search(modules path use_path_module)
	if (use_path_module)
		if (MSVC)
			hryky_link_libraries(Shlwapi)
		endif()
	endif()
	
	hryky_search(HRYKY_MINIMUM_MODULES ${module_name} is_prerequisite)
	if (is_prerequisite) 
		foreach(module ${modules})
			hryky_debug("${PROJECT_NAME} depends on hryky_${module}")
			hryky_append_module_includes(${module})
		endforeach()
	else()
		foreach(module ${modules})
			if (TARGET hryky_${module})
				hryky_debug("${module} has been already configured." )
			else()
				hryky_search(HRYKY_MINIMUM_MODULES ${module} is_prerequisite)
				if (NOT is_prerequisite)
					hryky_debug("${PROJECT_NAME} depends on hryky_${module}")
					add_subdirectory(
						${HRYKY_CODEBASE_ROOT}/lib/${module}
						${HRYKY_MODULE_BINARY_ROOT}/${module})
				endif()
			endif()
			
			hryky_append_module_includes(${module})
			hryky_search(
				HRYKY_LIBRARY_PROJECTS 
				hryky_${module}
				is_library_project)
			if (is_library_project)
				hryky_link_libraries(hryky_${module})
			endif()
			
		endforeach()
	endif()

	hryky_ascend()
	hryky_debug("} ${PROJECT_NAME} ends to use ${modules}")

endfunction()

#-------------------------------------------------------------------------------
# appends include directories to use a module
#-------------------------------------------------------------------------------
function(hryky_append_module_includes module)
	if (TARGET hryky_${module})
		get_target_property(module_includes hryky_${module} INCLUDE_DIRECTORIES)
		hryky_append_includes(${module_includes})
	else()
		hryky_append_includes(
			${HRYKY_CODEBASE_ROOT}/lib/${module}/include
			${HRYKY_MODULE_BINARY_ROOT}/${module}/include
			${HRYKY_CODEBASE_ROOT}/lib/${module}/${HRYKY_PLATFORM_NAME}/include
			${HRYKY_MODULE_BINARY_ROOT}/${module}/${HRYKY_PLATFORM_NAME}/include
			)
	endif()
endfunction()

#-------------------------------------------------------------------------------
# append include directories
#-------------------------------------------------------------------------------
function(hryky_append_includes)
	get_target_property(project_includes ${PROJECT_NAME} INCLUDE_DIRECTORIES)
	if (project_includes)
		if (ARGN)
			list(APPEND project_includes ${ARGN})
		endif()
	else()
		if (ARGN)
			set(project_includes ${ARGN})
		else()
			return()
		endif()
	endif()
	list(REMOVE_DUPLICATES project_includes)
	set_target_properties(${PROJECT_NAME}
		PROPERTIES INCLUDE_DIRECTORIES "${project_includes}")
	# hryky_debug("${PROJECT_NAME} includes: ${project_includes}")
endfunction()

#-------------------------------------------------------------------------------
# uses precompiled header.
# param : {string} pch_header is the name of precompiled header.
# param : {string} pch_source is the path to a precompiled source file.
# param : {variable} cpp_sources is the list of cpp source files.
#-------------------------------------------------------------------------------
function(hryky_use_precompiled_header pch_header pch_source cpp_sources_var)
	if(MSVC)
		get_filename_component(pch_source ${pch_source} ABSOLUTE)
	
		# creates precompiled header
		hryky_append_file_compile_flags(
			${pch_source} 
			/Yc\"${pch_header}\" 
			/Fp\"$(IntDir)/${pch_header}.pch\")
		
		# removes the precompiled source from normal sources
		list(REMOVE_ITEM ${cpp_sources_var} ${pch_source})
		
		list(LENGTH ${cpp_sources_var} cpp_sources_length)
		
		if (cpp_sources_length)
			# uses precompiled header
			set(ADDITIONAL_FLAGS
				/Yu\"${pch_header}\" 
				/Fp\"$(IntDir)/${pch_header}.pch\")
			hryky_append_files_compile_flags(
				${cpp_sources_var} ADDITIONAL_FLAGS)
		endif()
		list(APPEND ${cpp_sources_var} ${pch_source})
		hryky_export_var_quietly(${cpp_sources_var})
	endif(MSVC)
endfunction()

#-------------------------------------------------------------------------------
# prints the variables that change the behavior of CMake.
#-------------------------------------------------------------------------------
function(hryky_print_behavioral_variables)
	hryky_print_var(BUILD_SHARED_LIBS)
	hryky_print_var(CMAKE_BACKWARD_COMPATIBILITY)
	hryky_print_var(CMAKE_BUILD_TYPE)
	hryky_print_var(CMAKE_COLOR_MAKEFILE)
	hryky_print_var(CMAKE_CONFIGURATION_TYPES)
	hryky_print_var(CMAKE_FIND_LIBRARY_PREFIXES)
	hryky_print_var(CMAKE_FIND_LIBRARY_SUFFIXES)
	hryky_print_var(CMAKE_IGNORE_PATH)
	hryky_print_var(CMAKE_INCLUDE_PATH)
	hryky_print_var(CMAKE_INSTALL_PREFIX)
	hryky_print_var(CMAKE_LIBRARY_PATH)
	hryky_print_var(CMAKE_MFC_FLAG)
	hryky_print_var(CMAKE_MODULE_PATH)
	hryky_print_var(CMAKE_NOT_USING_CONFIG_FLAGS)
	hryky_print_var(CMAKE_PREFIX_PATH)
	hryky_print_var(CMAKE_PROGRAM_PATH)
	hryky_print_var(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY)
	hryky_print_var(CMAKE_SYSTEM_IGNORE_PATH)
	hryky_print_var(CMAKE_SYSTEM_INCLUDE_PATH)
	hryky_print_var(CMAKE_SYSTEM_LIBRARY_PATH)
	hryky_print_var(CMAKE_SYSTEM_PREFIX_PATH)
	hryky_print_var(CMAKE_SYSTEM_PROGRAM_PATH)
	hryky_print_var(CMAKE_USER_MAKE_RULES_OVERRIDE)
endfunction()

#-------------------------------------------------------------------------------
# prints the variables of CMake system.
#-------------------------------------------------------------------------------
function(hryky_print_system_variables)
	hryky_print_var(APPLE)
	hryky_print_var(BORLAND)
	hryky_print_var(CMAKE_CL_64)
	hryky_print_var(CMAKE_COMPILER_2005)
	hryky_print_var(CMAKE_HOST_APPLE)
	hryky_print_var(CMAKE_HOST_SYSTEM)
	hryky_print_var(CMAKE_HOST_SYSTEM_NAME)
	hryky_print_var(CMAKE_HOST_SYSTEM_PROCESSOR)
	hryky_print_var(CMAKE_HOST_SYSTEM_VERSION)
	hryky_print_var(CMAKE_HOST_UNIX)
	hryky_print_var(CMAKE_HOST_WIN32)
	hryky_print_var(CMAKE_OBJECT_PATH_MAX)
	hryky_print_var(CMAKE_OBJECT_PATH_MAX)
	hryky_print_var(CMAKE_SYSTEM)
	hryky_print_var(CMAKE_SYSTEM_NAME)
	hryky_print_var(CMAKE_SYSTEM_PROCESSOR)
	hryky_print_var(CMAKE_SYSTEM_VERSION)
	hryky_print_var(CYGWIN)
	hryky_print_var(MSVC)
	hryky_print_var(MSVC80)
	hryky_print_var(MSVC_IDE)
	hryky_print_var(MSVC_VERSION)
	hryky_print_var(UNIX)
	hryky_print_var(WIN32)
	hryky_print_var(XCODE_VERSION)

	hryky_print_var(CMAKE_FRAMEWORK_PATH)
	hryky_print_var(CMAKE_SYSTEM_FRAMEWORK_PATH)
	hryky_print_var(CMAKE_TOOLCHAIN_FILE)
endfunction()

#-------------------------------------------------------------------------------
# prints the variables for each language.
# param: {string} lang is the identifier of language. e.g. C, CXX
#-------------------------------------------------------------------------------
function(hryky_print_language_variables lang)
	hryky_print_var(CMAKE_${lang}_ARCHIVE_APPEND)
	hryky_print_var(CMAKE_${lang}_ARCHIVE_CREATE)
	hryky_print_var(CMAKE_${lang}_ARCHIVE_FINISH)
	hryky_print_var(CMAKE_${lang}_COMPILER)
	hryky_print_var(CMAKE_${lang}_COMPILER_ABI)
	hryky_print_var(CMAKE_${lang}_COMPILER_ID)
	hryky_print_var(CMAKE_${lang}_COMPILER_LOADED)
	hryky_print_var(CMAKE_${lang}_COMPILE_OBJECT)
	hryky_print_var(CMAKE_${lang}_CREATE_SHARED_LIBRARY)
	hryky_print_var(CMAKE_${lang}_CREATE_SHARED_MODULE)
	hryky_print_var(CMAKE_${lang}_CREATE_STATIC_LIBRARY)
	hryky_print_var(CMAKE_${lang}_FLAGS_DEBUG)
	hryky_print_var(CMAKE_${lang}_FLAGS_MINSIZEREL)
	hryky_print_var(CMAKE_${lang}_FLAGS_RELEASE)
	hryky_print_var(CMAKE_${lang}_FLAGS_RELWITHDEBINFO)
	hryky_print_var(CMAKE_${lang}_IGNORE_EXTENSIONS)
	hryky_print_var(CMAKE_${lang}_IMPLICIT_INCLUDE_DIRECTORIES)
	hryky_print_var(CMAKE_${lang}_IMPLICIT_LINK_DIRECTORIES)
	hryky_print_var(CMAKE_${lang}_IMPLICIT_LINK_LIBRARIES)
	hryky_print_var(CMAKE_${lang}_LINKER_PREFERENCE)
	hryky_print_var(CMAKE_${lang}_LINKER_PREFERENCE_PROPAGATES)
	hryky_print_var(CMAKE_${lang}_LINK_EXECUTABLE)
	hryky_print_var(CMAKE_${lang}_OUTPUT_EXTENSION)
	hryky_print_var(CMAKE_${lang}_PLATFORM_ID)
	hryky_print_var(CMAKE_${lang}_SIZEOF_DATA_PTR)
	hryky_print_var(CMAKE_${lang}_SOURCE_FILE_EXTENSIONS)
	hryky_print_var(CMAKE_COMPILER_IS_GNU${lang})
	hryky_print_var(CMAKE_USER_MAKE_RULES_OVERRIDE_${lang})
endfunction()

#-------------------------------------------------------------------------------
# prints the variables for C language.
#-------------------------------------------------------------------------------
function(hryky_print_c_variables)
	hryky_print_language_variables(C)
endfunction()

#-------------------------------------------------------------------------------
# prints the variables for C++.
#-------------------------------------------------------------------------------
function(hryky_print_cxx_variables)
	hryky_print_language_variables(CXX)
endfunction()

#-------------------------------------------------------------------------------
# prints the variables of the target project.
#-------------------------------------------------------------------------------
function(hryky_print_project_variables)
	hryky_print_var(CMAKE_AR)
	hryky_print_var(CMAKE_BINARY_DIR)
	hryky_print_var(CMAKE_BUILD_TOOL)
	hryky_print_var(CMAKE_CACHE_MAJOR_VERSION)
	hryky_print_var(CMAKE_CACHE_MINOR_VERSION)
	hryky_print_var(CMAKE_CACHE_PATCH_VERSION)
	hryky_print_var(CMAKE_CACHEFILE_DIR)
	hryky_print_var(CMAKE_CFG_INTDIR)
	hryky_print_var(CMAKE_COMMAND)
	hryky_print_var(CMAKE_CROSSCOMPILING)
	hryky_print_var(CMAKE_CTEST_COMMAND)
	hryky_print_var(CMAKE_CURRENT_BINARY_DIR)
	hryky_print_var(CMAKE_CURRENT_LIST_DIR)
	hryky_print_var(CMAKE_CURRENT_LIST_FILE)
	hryky_print_var(CMAKE_CURRENT_LIST_LINE)
	hryky_print_var(CMAKE_CURRENT_SOURCE_DIR)
	hryky_print_var(CMAKE_DL_LIBS)
	hryky_print_var(CMAKE_EDIT_COMMAND)
	hryky_print_var(CMAKE_EXECUTABLE_SUFFIX)
	hryky_print_var(CMAKE_EXTRA_GENERATOR)
	hryky_print_var(CMAKE_EXTRA_GENERATOR)
	hryky_print_var(CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES)
	hryky_print_var(CMAKE_GENERATOR)
	hryky_print_var(CMAKE_HOME_DIRECTORY)
	hryky_print_var(CMAKE_IMPORT_LIBRARY_PREFIX)
	hryky_print_var(CMAKE_IMPORT_LIBRARY_SUFFIX)
	hryky_print_var(CMAKE_LINK_LIBRARY_SUFFIX)
	hryky_print_var(CMAKE_MAJOR_VERSION)
	hryky_print_var(CMAKE_MAKE_PROGRAM)
	hryky_print_var(CMAKE_MINOR_VERSION)
	hryky_print_var(CMAKE_PARENT_LIST_FILE)
	hryky_print_var(CMAKE_PATCH_VERSION)
	hryky_print_var(CMAKE_PROJECT_NAME)
	hryky_print_var(CMAKE_RANLIB)
	hryky_print_var(CMAKE_ROOT)
	hryky_print_var(CMAKE_SHARED_LIBRARY_PREFIX)
	hryky_print_var(CMAKE_SHARED_LIBRARY_SUFFIX)
	hryky_print_var(CMAKE_SHARED_MODULE_PREFIX)
	hryky_print_var(CMAKE_SHARED_MODULE_SUFFIX)
	hryky_print_var(CMAKE_SIZEOF_VOID_P)
	hryky_print_var(CMAKE_SKIP_RPATH)
	hryky_print_var(CMAKE_SOURCE_DIR)
	hryky_print_var(CMAKE_STANDARD_LIBRARIES)
	hryky_print_var(CMAKE_STATIC_LIBRARY_PREFIX)
	hryky_print_var(CMAKE_STATIC_LIBRARY_SUFFIX)
	hryky_print_var(CMAKE_TWEAK_VERSION)
	hryky_print_var(CMAKE_USING_VC_FREE_TOOLS)
	hryky_print_var(CMAKE_VERBOSE_MAKEFILE)
	hryky_print_var(CMAKE_VERSION)
	
	hryky_print_var(PROJECT_BINARY_DIR)
	hryky_print_var(PROJECT_NAME)
	hryky_print_var(PROJECT_SOURCE_DIR)
	hryky_print_var(${PROJECT_NAME}_BINARY_DIR)
	hryky_print_var(${PROJECT_NAME}_SOURCE_DIR)
endfunction()

#-------------------------------------------------------------------------------
# uses boost c++ library
# http://www.boost.org/
#
# output variables to the parent directory
#   HRYKY_BOOST_COMPONENTS is the list of the used components of Boost.
#   HRYKY_BOOST_LIBRARIES is the list of the libraries of Boost.
#   HRYKY_BOOST_INCLUDES is the list of include directories of Boost.
#-------------------------------------------------------------------------------
function(hryky_use_boost)

	set(Boost_USE_STATIC_LIBS ON
		CACHE BOOL "creates Boost as static library.")
	set(Boost_USE_STATIC_RUNTIME ${HRYKY_USE_STATIC_CRT}
		CACHE BOOL "uses Boost with the static runtime libraries.")
	set(Boost_USE_MULTITHREADED ON
		CACHE BOOL "uses Boost with the multi-threaded runtime libraries.")
	set(Boost_DETAILED_FAILURE_MSG ON
		CACHE BOOL "outputs the detailed message about failure of finding Boost.")
	set(Boost_DEBUG ON 
		CACHE BOOL "outputs the message about finding Boost.")
	set(BOOST_THREAD_DONT_USE_CHRONO 0
		CACHE BOOL "prevents Boost.Thread front using Boost.Chrono.")
	
	set(components ${ARGV})

	# replaces the keyword "asio" to appropriate names.
	hryky_search(components asio use_asio)
	if (use_asio)
		list(REMOVE_ITEM components asio)
		list(APPEND components system thread date_time regex serialization)
		list(REMOVE_DUPLICATES components)
	endif()
	
	# appends chrono for Boost.Thread untile BOOST_THREAD_DONT_USE_CHRONO is enabled.
	hryky_search(components thread use_thread)
	if (use_thread AND (NOT BOOST_THREAD_DONT_USE_CHRONO))
		list(APPEND components chrono)
		list(REMOVE_DUPLICATES components)
	endif()

	hryky_begin_external("Boost C++ Libraries")
	
	if (DEFINED HRYKY_BOOST_COMPONENTS)
		foreach(component ${components})
			list(FIND 
				HRYKY_BOOST_COMPONENTS ${component} component_found)
			hryky_debug("component found ${component} ${component_found}")
			if (${component_found} EQUAL -1)
				list(APPEND new_components ${component})
			endif()
		endforeach()
		if (NOT new_components)
			hryky_debug("skips finding Boost components.")
			set(skip_finding TRUE)
		else()
			hryky_print_var(new_components)
			list(APPEND HRYKY_BOOST_COMPONENTS ${new_components})
		endif()
	else()
		hryky_debug("starts to find Boost components.")
		set(HRYKY_BOOST_COMPONENTS ${components})
	endif()
	
	set(Boost_COMPONENTS ${HRYKY_BOOST_COMPONENTS})
	
	if (NOT skip_finding)
		hryky_debug("starts to find Boost components: ${Boost_COMPONENTS}")

		if (MSVC)
			if (CMAKE_SIZEOF_VOID_P EQUAL 8)
				set(BOOST_ROOT $ENV{ProgramW6432}/Boost)
			else()
				set(BOOST_ROOT $ENV{ProgramFiles}/Boost)
			endif()
			set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
			set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
		endif()
	
		hryky_print_var(BOOST_LIBRARYDIR)
		hryky_print_var(Boost_USE_MULTITHREADED)
		hryky_print_var(Boost_USE_STATIC_LIBS)
		hryky_print_var(Boost_NO_SYSTEM_PATHS)
		hryky_print_var(Boost_NO_BOOST_CMAKE)
		hryky_print_var(Boost_USE_STATIC_RUNTIME)
		hryky_print_var(Boost_USE_DEBUG_PYTHON)
		hryky_print_var(Boost_USE_STLPORT)
		hryky_print_var(Boost_ADITIONAL_VERSIONS)
		hryky_print_var(Boost_DEBUG)
		hryky_print_var(Boost_DETAILED_FAILURE_MSG)
		hryky_print_var(Boost_COMPILER)
		hryky_print_var(Boost_THREADAPI)
		hryky_print_var(Boost_REALPATH)
	
		set(HRYKY_BOOST_VERSIONS 1.55.0 1.54.0 1.53.0 1.52.0
			CACHE STRING "The candidates of the version of Boost")

		foreach(version ${HRYKY_BOOST_VERSIONS})
			find_package(Boost ${version} COMPONENTS ${Boost_COMPONENTS})
			
			if (Boost_FOUND)
				break()
			endif()
		endforeach()
		
		if (NOT Boost_FOUND)
			hryky_emerg("Boost C++ Library is not found.")
		endif()
	
		hryky_print_var(Boost_VERSION)
		hryky_print_var(Boost_LIB_VERSION)
		hryky_print_var(Boost_MAJOR_VERSION)
		hryky_print_var(Boost_MINOR_VERSION)
		hryky_print_var(Boost_SUBMINOR_VERSION)
		hryky_print_var(Boost_FOUND)
		hryky_print_var(BOOST_ROOT)
		hryky_print_var(Boost_LIBRARY_DIRS)
		hryky_print_var(Boost_INCLUDE_DIR)
		hryky_print_var(Boost_LIBRARIES)

		set(HRYKY_BOOST_LIBRARIES ${Boost_LIBRARIES})
		set(HRYKY_BOOST_INCLUDES ${Boost_INCLUDE_DIR})
	endif()

	add_definitions(-DHRYKY_USE_BOOST=1)

	if (use_asio)
		add_definitions(-DHRYKY_USE_BOOST_ASIO=1)
	endif()
	
	list(FIND components filesystem use_filesystem)
	if (use_filesystem)
		add_definitions(-DHRYKY_USE_BOOST_FILESYSTEM=1)
	endif()

	list(FIND components thread use_thread)
	if (use_thread)
		add_definitions(-DHRYKY_USE_BOOST_EXCLUSION=1)
	endif()
	
	hryky_append_directory_property(
		COMPILE_DEFINITIONS_DEBUG BOOST_ENABLE_ASSERT_HANDLER)
	hryky_append_directory_property(
		COMPILE_DEFINITIONS_RELEASE BOOST_DISABLE_ASSERTS)
	if (MSVC10)
		add_definitions(-DBOOST_NO_RVALUE_REFERENCES)
	endif()
	add_definitions(-DBOOST_BIND_NO_PLACEHOLDERS)
	
	hryky_append_includes(${HRYKY_BOOST_INCLUDES})
	hryky_link_libraries(${HRYKY_BOOST_LIBRARIES})
	
	hryky_export_var(HRYKY_BOOST_LIBRARIES)
	hryky_export_var(HRYKY_BOOST_COMPONENTS)
	hryky_export_var(HRYKY_BOOST_INCLUDES)

	hryky_end_external()
	
endfunction()

#-------------------------------------------------------------------------------
# uses OpenGL
# http://www.opengl.org/
#
# outputs the following variables to the parent scope.
#   HRYKY_OPENGL_SEARCHED is the history of finding OpenGL.
#   HRYKY_OPENGL_LIBRARIES is the list of libraries of OpenGL.
#   HRYKY_OPENGL_INCLUDES is the list of include directories of OpenGL.
#-------------------------------------------------------------------------------
function(hryky_use_gl)
	hryky_begin_external("OpenGL")
	
	if (NOT DEFINED HRYKY_OPENGL_SEARCHED)
		find_package(OpenGL)
		if(NOT OPENGL_FOUND)
			hryky_emerg("OpenGL is not found.")
		endif()
		
		hryky_print_var(OPENGL_FOUND)
		hryky_print_var(OPENGL_XMESA_FOUND)
		hryky_print_var(OPENGL_GLU_FOUND)
		hryky_print_var(OPENGL_INCLUDE_DIR)
		hryky_print_var(OPENGL_LIBRARIES)
		hryky_print_var(OPENGL_gl_LIBRARY)
		hryky_print_var(OPENGL_glu_LIBRARY)
		
		set(HRYKY_OPENGL_INCLUDES ${OPENGL_INCLUDE_DIR})
		set(HRYKY_OPENGL_LIBRARIES ${OPENGL_gl_LIBRARY})
		
		set(HRYKY_OPENGL_SEARCHED true)
		
		hryky_export_var(HRYKY_OPENGL_SEARCHED)
		hryky_export_var(HRYKY_OPENGL_LIBRARIES)
		hryky_export_var(HRYKY_OPENGL_INCLUDES)
	endif()

	hryky_append_includes(${HRYKY_OPENGL_INCLUDES})
	hryky_link_libraries(${HRYKY_OPENGL_LIBRARIES})
	
	hryky_end_external()
	
endfunction()

#-------------------------------------------------------------------------------
# uses OpenAL Soft
# http://kcat.strangesoft.net/openal.html
#
# outputs the following variables to the parent scope.
#   HRYKY_OPENAL_SEARCHED is the history of finding OpenAL.
#   HRYKY_OPENAL_LIBRARIES is the list of libraries of OpenAL.
#   HRYKY_OPENAL_INCLUDES is the list of include directories of OpenAL.
#-------------------------------------------------------------------------------
function(hryky_use_openal)
	hryky_begin_external("OpenAL")

	if (NOT DEFINED HRYKY_OPENAL_SEARCHED)
		if (WIN32)
			if (HRYKY_ARCH64)
				set(ENV{OPENALDIR} $ENV{ProgramW6432}/OpenAL)
			else()
				set(ENV{OPENALDIR} $ENV{ProgramFiles}/OpenAL)
			endif()
		endif()
		find_package(OpenAL)
		if(NOT OPENAL_INCLUDE_DIR)
			hryky_emerg("OpenAL is not found.")
		endif()
		
		string(REGEX REPLACE "/AL" "" OPENAL_INCLUDE_DIR "${OPENAL_INCLUDE_DIR}")
		
		hryky_print_var(OPENAL_INCLUDE_DIR)
		hryky_print_var(OPENAL_LIBRARY)
		
		set(HRYKY_OPENAL_SEARCHED true)
		set(HRYKY_OPENAL_INCLUDES ${OPENAL_INCLUDE_DIR})
		set(HRYKY_OPENAL_LIBRARIES ${OPENAL_LIBRARY})
	
		hryky_export_var(HRYKY_OPENAL_SEARCHED)
		hryky_export_var(HRYKY_OPENAL_LIBRARIES)
		hryky_export_var(HRYKY_OPENAL_INCLUDES)
	endif()

	hryky_append_includes(${HRYKY_OPENAL_INCLUDES})
	hryky_link_libraries(${HRYKY_OPENAL_LIBRARIES})
	
	hryky_end_external()
endfunction()
#-------------------------------------------------------------------------------
# uses OpenSSL
# http://www.openssl.org/
#
# outputs the following variables to the parent scope.
#   HRYKY_OPENSSL_SEARCHED is the history of finding OpenSSL.
#   HRYKY_OPENSSL_LIBRARIES is the list of libraries of OpenSSL.
#   HRYKY_OPENSSL_INCLUDES is the list of include directories of OpenSSL.
#-------------------------------------------------------------------------------
function(hryky_use_openssl)
	hryky_begin_external("OpenSSL")
	
	if (NOT DEFINED HRYKY_OPENSSL_SEARCHED)
		if (MSVC)
			if (HRYKY_ARCH64)
				set(OPENSSL_ROOT_DIR $ENV{ProgramW6432}/openssl)
			else()
				set(OPENSSL_ROOT_DIR $ENV{ProgramFiles}/openssl)
			endif()
		endif()
		hryky_print_var(OPENSSL_ROOT_DIR)
		
		find_package(OpenSSL)
	
		if (NOT OPENSSL_FOUND)
			hryky_emerg("OpenSSL is not found.")
			return()
		endif()
		
		hryky_print_var(OPENSSL_FOUND)
		hryky_print_var(OPENSSL_INCLUDE_DIR)
		hryky_print_var(OPENSSL_LIBRARIES)
		hryky_print_var(OPENSSL_VERSION)
	
		set(HRYKY_OPENSSL_SEARCHED true)
		set(HRYKY_OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES})
		set(HRYKY_OPENSSL_INCLUDES ${OPENSSL_INCLUDE_DIR})

		hryky_export_var(HRYKY_OPENSSL_SEARCHED)
		hryky_export_var(HRYKY_OPENSSL_LIBRARIES)
		hryky_export_var(HRYKY_OPENSSL_INCLUDES)
	endif()

	add_definitions(-DHRYKY_USE_OPENSSL=1)

	hryky_link_libraries(${HRYKY_OPENSSL_LIBRARIES})
	hryky_append_includes(${HRYKY_OPENSSL_INCLUDES})
	
	hryky_end_external()
	
endfunction()

#-------------------------------------------------------------------------------
# uses SDL
# http://www.libsdl.org/
#
# outputs the following variables to the parent scope.
#   HRYKY_SDL_SEARCHED is the history of finding SDL.
#   HRYKY_SDL_LIBRARIES is the list of libraries of SDL.
#   HRYKY_SDL_INCLUDES is the list of include directories of SDL.
#-------------------------------------------------------------------------------
function(hryky_use_sdl)
	hryky_begin_external("SDL(Simple DirectMedia Layer)")
	
	if (NOT DEFINED HRYKY_SDL_SEARCHED)
		if (NOT HRYKY_CODEBASE_ROOT)
			hryky_emerg("HRYKY_CODEBASE_ROOT is not defined.")
		endif()
		
		find_package(SDL)
		
		if(NOT SDL_FOUND)
			set(SDL_INCLUDE_DIR       ${HRYKY_EXTERNAL_DIR}/SDL/include)
			set(SDL_LIBRARY_PREFIX    ${HRYKY_EXTERNAL_DIR}/SDL/lib)
			if (MSVC)
				if (CMAKE_SIZEOF_VOID_P EQUAL 8)
					set(SDL_LIBRARIES
						debug       ${SDL_LIBRARY_PREFIX}/win/x64/Debug/SDL.lib
						debug       ${SDL_LIBRARY_PREFIX}/win/x64/Debug/SDLmain.lib
						optimized   ${SDL_LIBRARY_PREFIX}/win/x64/Release/SDL.lib
						optimized   ${SDL_LIBRARY_PREFIX}/win/x64/Release/SDLmain.lib)
				else()
					set(SDL_LIBRARIES
						debug       ${SDL_LIBRARY_PREFIX}/win/x86/Debug/SDL.lib
						debug       ${SDL_LIBRARY_PREFIX}/win/x86/Debug/SDLmain.lib
						optimized   ${SDL_LIBRARY_PREFIX}/win/x86/Release/SDL.lib
						optimized   ${SDL_LIBRARY_PREFIX}/win/x86/Release/SDLmain.lib)
				endif()
			else()
				hryky_emerg("SDL is not found.")
			endif()
		endif()
		
		hryky_print_var(SDL_FOUND)
		hryky_print_var(SDL_INCLUDE_DIR)
		hryky_print_var(SDL_LIBRARIES)
		
		set(HRYKY_SDL_SEARCHED true)
		set(HRYKY_SDL_LIBRARIES ${SDL_LIBRARIES})
		set(HRYKY_SDL_INCLUDES ${SDL_INCLUDE_DIR})
		
		if (MSVC)
			list(APPEND HRYKY_SDL_LIBRARIES winmm imm32 version)
		endif()
		
		hryky_export_var(HRYKY_SDL_SEARCHED)
		hryky_export_var(HRYKY_SDL_LIBRARIES)
		hryky_export_var(HRYKY_SDL_INCLUDES)
	endif()
	
	add_definitions(-DHRYKY_USE_SDL=1 -DSDL_MAIN_HANDLED)

	hryky_link_libraries(${HRYKY_SDL_LIBRARIES})
	hryky_append_includes(${HRYKY_SDL_INCLUDES})

	hryky_end_external()
endfunction()

#-------------------------------------------------------------------------------
# uses FreeGLUT
# http://freeglut.sourceforge.net/
#
# outputs the following variables to the parent scope.
#   HRYKY_FREEGLUT_SEARCHED is the history of finding FreeGLUT.
#   HRYKY_FREEGLUT_LIBRARIES is the list of libraries of FreeGLUT.
#   HRYKY_FREEGLUT_INCLUDES is the list of include directories of FreeGLUT.
#-------------------------------------------------------------------------------
function(hryky_use_freeglut)
	hryky_begin_external("FreeGLUT")
	
	if (NOT DEFINED HRYKY_FREEGLUT_SEARCHED)
		if (NOT HRYKY_CODEBASE_ROOT)
			hryky_emerg("HRYKY_CODEBASE_ROOT is not defined.")
		endif()
		
		find_package(FreeGLUT)
		
		if(NOT FREEGLUT_FOUND)
			set(FREEGLUT_INCLUDE_DIR       ${HRYKY_EXTERNAL_DIR}/freeglut/include)
			set(FREEGLUT_LIBRARY_PREFIX    ${HRYKY_EXTERNAL_DIR}/freeglut/lib)
			if (MSVC)
				if (CMAKE_SIZEOF_VOID_P EQUAL 8)
					set(FREEGLUT_LIBRARIES
						debug       ${FREEGLUT_LIBRARY_PREFIX}/win/x64/Debug/freeglut_static.lib
						optimized   ${FREEGLUT_LIBRARY_PREFIX}/win/x64/Release/freeglut_static.lib
						)
				else()
					set(FREEGLUT_LIBRARIES
						debug       ${FREEGLUT_LIBRARY_PREFIX}/win/x86/Debug/freeglut_static.lib
						optimized   ${FREEGLUT_LIBRARY_PREFIX}/win/x86/Release/freeglut_static.lib
						)
				endif()
			else()
				hryky_emerg("FreeGLUT is not found.")
			endif()
		endif()
		
		hryky_print_var(FREEGLUT_FOUND)
		hryky_print_var(FREEGLUT_INCLUDE_DIR)
		hryky_print_var(FREEGLUT_LIBRARIES)
		
		
		set(HRYKY_FREEGLUT_SEARCHED true)
		set(HRYKY_FREEGLUT_LIBRARIES ${FREEGLUT_LIBRARIES})
		set(HRYKY_FREEGLUT_INCLUDES ${FREEGLUT_INCLUDE_DIR})
		
		if (MSVC)
			# list(APPEND HRYKY_FREEGLUT_LIBRARIES winmm imm32 version)
		endif()
		
		hryky_export_var(HRYKY_FREEGLUT_SEARCHED)
		hryky_export_var(HRYKY_FREEGLUT_LIBRARIES)
		hryky_export_var(HRYKY_FREEGLUT_INCLUDES)
	endif()
	
	add_definitions(-DHRYKY_USE_FREEGLUT=1)
	hryky_append_includes(${HRYKY_FREEGLUT_INCLUDES})
	hryky_link_libraries(${HRYKY_FREEGLUT_LIBRARIES})

	hryky_end_external()
endfunction()

#-------------------------------------------------------------------------------
# uses IPAFont
#-------------------------------------------------------------------------------
function(hryky_use_ipafont)
	hryky_begin_external("IPAFont resources")
	
	set(HRYKY_IPAFONT_DIR ${HRYKY_EXTERNAL_DIR}/IPAfont)
	set(HRYKY_IPAEXFONT_DIR ${HRYKY_EXTERNAL_DIR}/IPAexfont)
	
	file(GLOB ipafont_ttfs ${HRYKY_IPAFONT_DIR}/*.ttf)
	file(GLOB ipaexfont_ttfs ${HRYKY_IPAEXFONT_DIR}/*.ttf)
	
	list(APPEND ttfs ${ipafont_ttfs} ${ipaexfont_ttfs})
	
	foreach(ttf ${ttfs})
		string(
			REGEX REPLACE 
			"${HRYKY_CODEBASE_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}"
			target_ttf ${ttf})
		list(APPEND target_ttfs ${target_ttf})
		add_custom_command(
			OUTPUT ${target_ttf}
			COMMAND ${CMAKE_COMMAND}
			ARGS -E copy "${ttf}" "${target_ttf}"
			DEPENDS ${ttf}
			COMMENT "deploys TTF file from ${ttf} to ${target_ttf}"
			VERBATIM)
	endforeach()
	
	add_custom_target(ipafont 
		DEPENDS ${target_ttfs}
		COMMENT "deploys IPAFont TTF files")
	add_dependencies(${PROJECT_NAME} ipafont)

	hryky_end_external()
endfunction()

#-------------------------------------------------------------------------------
# uses V8 JavaScript Engine
# https://code.google.com/p/v8/
#
# output variables to the parent scope:
#   HRYKY_V8_SEARCHED is the history of finding V8.
#   HRYKY_V8_LIBRARIES is the list of libraries of V8.
#   HRYKY_V8_INCLUDES is the list of include directories of V8.
#-------------------------------------------------------------------------------
function(hryky_use_v8)
	hryky_begin_external("V8 JavaScript Engine")
	
	if (NOT DEFINED HRYKY_V8_SEARCHED)
		if (NOT HRYKY_CODEBASE_ROOT)
			hryky_emerg("HRYKY_CODEBASE_ROOT is not defined.")
		endif()
		
		find_package(V8)
		
		if(NOT V8_FOUND)
			set(V8_DIR                  ${HRYKY_EXTERNAL_DIR}/v8)
			set(V8_INCLUDE_DIR          ${V8_DIR}/include)
			set(V8_LIBRARY_DIR          ${V8_DIR}/lib)
			if (MSVC)
				if (CMAKE_SIZEOF_VOID_P EQUAL 8)
					set(V8_LIBRARIES
						debug       ${V8_LIBRARY_DIR}/win/x64/Debug/icui18n.lib
						debug       ${V8_LIBRARY_DIR}/win/x64/Debug/icuuc.lib
						debug       ${V8_LIBRARY_DIR}/win/x64/Debug/v8_base.lib
						debug       ${V8_LIBRARY_DIR}/win/x64/Debug/v8_libbase.x64.lib
						debug       ${V8_LIBRARY_DIR}/win/x64/Debug/v8_nosnapshot.lib
						optimized   ${V8_LIBRARY_DIR}/win/x64/Release/icui18n.lib
						optimized   ${V8_LIBRARY_DIR}/win/x64/Release/icuuc.lib
						optimized   ${V8_LIBRARY_DIR}/win/x64/Release/v8_base.lib
						optimized   ${V8_LIBRARY_DIR}/win/x64/Release/v8_libbase.x64.lib
						optimized   ${V8_LIBRARY_DIR}/win/x64/Release/v8_nosnapshot.lib
						)
				else()
					set(V8_LIBRARIES
						debug       ${V8_LIBRARY_DIR}/win/x86/Debug/icui18n.lib
						debug       ${V8_LIBRARY_DIR}/win/x86/Debug/icuuc.lib
						debug       ${V8_LIBRARY_DIR}/win/x86/Debug/v8_base.lib
						debug       ${V8_LIBRARY_DIR}/win/x86/Debug/v8_libbase.lib
						debug       ${V8_LIBRARY_DIR}/win/x86/Debug/v8_nosnapshot.lib
						optimized   ${V8_LIBRARY_DIR}/win/x86/Release/icui18n.lib
						optimized   ${V8_LIBRARY_DIR}/win/x86/Release/icuuc.lib
						optimized   ${V8_LIBRARY_DIR}/win/x86/Release/v8_base.lib
						optimized   ${V8_LIBRARY_DIR}/win/x86/Release/v8_libbase.lib
						optimized   ${V8_LIBRARY_DIR}/win/x86/Release/v8_nosnapshot.lib
						)
				endif()
			else()
				hryky_emerg("V8 JavaScript Engine is not found.")
			endif()
		endif()
		
		hryky_print_var(V8_FOUND)
		hryky_print_var(V8_INCLUDE_DIR)
		hryky_print_var(V8_LIBRARIES)
		
		set(HRYKY_V8_SEARCHED true)
		set(HRYKY_V8_LIBRARIES ${V8_LIBRARIES})
		set(HRYKY_V8_INCLUDES ${V8_INCLUDE_DIR})
	
		hryky_export_var(HRYKY_V8_SEARCHED)
		hryky_export_var(HRYKY_V8_LIBRARIES)
		hryky_export_var(HRYKY_V8_INCLUDES)
	endif()
	
	hryky_append_includes(${HRYKY_V8_INCLUDES})
	hryky_link_libraries(${HRYKY_V8_LIBRARIES})
	
	hryky_end_external()
endfunction()

#-------------------------------------------------------------------------------
# uses Protocol Buffers
# http://code.google.com/p/protobuf/
#
# output variables to the parent scope:
#   PROTOBUF_PROTOC_EXECUTABLE is the path to protoc.exe.
#   HRYKY_PROTOBUF_SEARCHED is the history of the finding.
#   HRYKY_PROTOBUF_LIBRARIES is the list of libraries to use V8.
#   HRYKY_PROTOBUF_INCLUDES is the list of include directories to use V8.
#-------------------------------------------------------------------------------
function(hryky_use_protobuf)
	hryky_begin_external("Protocol Buffers")
	
	if (DEFINED HRYKY_PROTOBUF_SEARCHED)
		if (NOT HRYKY_CODEBASE_ROOT)
			hryky_emerg("HRYKY_CODEBASE_ROOT is not defined.")
		endif()
		
		find_package(ProtocolBuffers)
		
		if(NOT PROTOBUF_FOUND)
			set(PROTOBUF_DIR              ${HRYKY_EXTERNAL_DIR}/protobuf/)
			set(PROTOBUF_INCLUDE_DIR      ${PROTOBUF_DIR}/include)
			set(PROTOBUF_LIBRARY_DIR      ${PROTOBUF_DIR}/lib)
			set(PROTOBUF_TOOL_DIR         ${PROTOBUF_DIR}/tool)
			if (MSVC)
				if (CMAKE_SIZEOF_VOID_P EQUAL 8)
					set(PROTOBUF_LIBRARIES
						debug       ${PROTOBUF_LIBRARY_DIR}/win/x64/Debug/libprotobuf.lib
						debug       ${PROTOBUF_LIBRARY_DIR}/win/x64/Debug/libprotobuf-lite.lib
						debug       ${PROTOBUF_LIBRARY_DIR}/win/x64/Debug/libprotoc.lib
						optimized   ${PROTOBUF_LIBRARY_DIR}/win/x64/Release/libprotobuf.lib
						optimized   ${PROTOBUF_LIBRARY_DIR}/win/x64/Release/libprotobuf-lite.lib
						optimized   ${PROTOBUF_LIBRARY_DIR}/win/x64/Release/libprotoc.lib
						)
					set(PROTOBUF_PROTOC_EXECUTABLE
						${PROTOBUF_TOOL_DIR}/win/x64/Release/protoc.exe)
				else()
					set(PROTOBUF_LIBRARIES
						debug       ${PROTOBUF_LIBRARY_DIR}/win/x86/Debug/libprotobuf.lib
						debug       ${PROTOBUF_LIBRARY_DIR}/win/x86/Debug/libprotobuf-lite.lib
						debug       ${PROTOBUF_LIBRARY_DIR}/win/x86/Debug/libprotoc.lib
						optimized   ${PROTOBUF_LIBRARY_DIR}/win/x86/Release/libprotobuf.lib
						optimized   ${PROTOBUF_LIBRARY_DIR}/win/x86/Release/libprotobuf-lite.lib
						optimized   ${PROTOBUF_LIBRARY_DIR}/win/x86/Release/libprotoc.lib
						)
					set(PROTOBUF_PROTOC_EXECUTABLE
						${PROTOBUF_TOOL_DIR}/win/x86/Release/protoc.exe)
				endif()
			else()
				hryky_emerg("Google ProtocolBuffers is not found.")
			endif()
		endif()
		
		hryky_print_var(PROTOBUF_FOUND)
		hryky_print_var(PROTOBUF_INCLUDE_DIR)
		hryky_print_var(PROTOBUF_LIBRARIES)
		hryky_print_var(PROTOBUF_PROTOC_EXECUTABLE)
		
		set(HRYKY_PROTOBUF_SEARCHED true)
		set(HRYKY_PROTOBUF_INCLUDES ${PROTOBUF_INCLUDE_DIR})
		set(HRYKY_PROTOBUF_LIBRARIES ${PROTOBUF_LIBRARIES})
		
		hryky_export_var(HRYKY_PROTOBUF_SEARCHED)
		hryky_export_var(HRYKY_PROTOBUF_LIBRARIES)
		hryky_export_var(HRYKY_PROTOBUF_INCLUDES)
		
		# The compiler of ProtocolBuffers are referred at the compilation.
		hryky_export_var(PROTOBUF_PROTOC_EXECUTABLE)
	endif()
	
	hryky_append_includes(${HRYKY_PROTOBUF_INCLUDES})
	hryky_link_libraries(${HRYKY_PROTOBUF_LIBRARIES})
	
	hryky_end_external()
	
endfunction()

#-------------------------------------------------------------------------------
# appends the rule to use Google Protocol Buffer.
# param : {string} proto is the path to the format file.
# param : {string} dest_dir is the path to which the serializer will be generated.
#-------------------------------------------------------------------------------
function(hryky_add_protobuf proto dest_dir)
	hryky_use_protobuf()

	if(EXISTS ${PROTOBUF_PROTOC_EXECUTABLE})
		hryky_emerg("ProtocolBuffers compiler is not found.")
		return()
	endif()
	
	get_filename_component(proto_name ${proto} NAME)
	get_filename_component(proto_name_we ${proto} NAME_WE)
	string(REPLACE ${proto_name} "" proto_dir ${proto})
	
	hryky_make_directory(${dest_dir})
	
	add_custom_command(
		OUTPUT 
			${dest_dir}/${proto_name_we}.pb.cc
			${dest_dir}/${proto_name_we}.pb.h
		COMMAND 
			${PROTOBUF_PROTOC_EXECUTABLE}
		ARGS
			-I${proto_dir}/
			--cpp_out=${dest_dir}
			${proto}
		DEPENDS 
			${PROTOBUF_PROTOC_EXECUTABLE} 
			${proto}
		COMMENT "generates the serializer ${proto_name_we}.pb.cc from ${proto}."
		VERBATIM)
	if(MSVC)
		hryky_append_file_compile_flags(
			${dest_dir}/${proto_name_we}.pb.cc
			/wd4127 /wd4244 /wd4267 /wd4512)
	endif()
endfunction()

#-------------------------------------------------------------------------------
# uses doxygen
# param : {variable} sources is the list of sources parsed by Doxygen.
#-------------------------------------------------------------------------------
function(hryky_use_doxygen sources)
	find_package(doxygen)
	hryky_print_var(DOXYGEN_FOUND)
	if (NOT DOXYGEN_FOUND)
		hryky_warn("Doxygen is not found.")
		return()
	endif()
	
	hryky_print_var(CMAKE_CURRENT_SOURCE_DIR)
		
	set(DOXYGEN_OUTPUT html latex
		CACHE STRING "The list of file extensions for which Doxygen outputs.")
	set(DOXYFILE etc/Doxyfile
		CACHE STRING "The path to Doxyfile read by Doxygen.")
	set(DOXYGEN_DEPENDS
		${DOXYFILE}
		etc/doxygen_header
		etc/doxygen_footer
		etc/doxygen.css
		CACHE STRING "The list of files on which the execution of doxygen depends.")

	add_custom_command(
		OUTPUT
			${DOXYGEN_OUTPUT} 
		COMMAND ${DOXYGEN_EXECUTABLE} 
			ARGS etc/Doxyfile
		DEPENDS ${${sources}} ${DOXYGEN_DEPENDS}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "doxygen : ${${sources}} are documented."
		VERBATIM)

	add_custom_target(
		${PROJECT_NAME} 
		DEPENDS
			${DOXYGEN_OUTPUT}
		)

	hryky_debug("doxygen : ${PROJECT_NAME}")
	# hryky_debug("doxygen_sources : ${${sources}}")

	install(DIRECTORY html
		DESTINATION ./doc/
		COMPONENT ${PROJECT_NAME}
		PATTERN "XTAGS" EXCLUDE
		PATTERN ".svn" EXCLUDE)
	
endfunction()

#-------------------------------------------------------------------------------
# static analysis by cppcheck
#  The C++ sources and headers are examined by Cppcheck.
# param : {string} dir is the root directory inspected by Cppcheck.
#-------------------------------------------------------------------------------
function(hryky_use_cppcheck dir)
	set(cppcheck_target ${PROJECT_NAME}_cppcheck)
	if (TARGET ${cppcheck_target})
		hryky_debug("${cppcheck_target} is already appended.")
		return()
	endif()
	
	find_program(CPPCHECK cppcheck PATH_SUFFIXES Cppcheck)
	hryky_print_var(CPPCHECK)
	if (NOT CPPCHECK)
		hryky_warn("CppCheck is not found.")
		return()
	endif()
	
	hryky_begin_external("cppcheck")
	
	hryky_find_file_recurse(cppcheck_sources ${dir}/*.c)
	hryky_find_file_recurse(cppcheck_sources ${dir}/*.cpp)
	hryky_find_file_recurse(cppcheck_sources ${dir}/*.cc)
	hryky_find_file_recurse(cppcheck_sources ${dir}/*.h)
	hryky_find_file_recurse(cppcheck_sources ${dir}/*.hpp)
	
	hryky_print_var(cppcheck_sources)

	set(cppcheck_result 
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_cppcheck_result.txt)
	add_custom_target(
		${cppcheck_target}
		COMMAND ${CPPCHECK}
			--enable=all
			--error-exitcode=1
			--errorlist
			--check-config
			--report-progress
			--template vs
			--verbose
			${dir} > ${cppcheck_result}
		DEPENDS ${cppcheck_sources}
		COMMENT 
			"cppcheck ${CMAKE_CURRENT_SOURCE_DIR} to ${cppcheck_result}"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		VERBATIM
		SOURCES ${cppcheck_sources}
		)
	add_dependencies(${PROJECT_NAME} ${cppcheck_target})
	
	hryky_end_external()
endfunction()

#-------------------------------------------------------------------------------
# appends the rule to generate the Kmyacc parser.
# param : {string} grammar is the path to the grammar file.
# param : {string} dest_dir is the path in which the parser will be generated.
#-------------------------------------------------------------------------------
function(hryky_add_kmyacc_parser grammar dest_dir)
	if (NOT HRYKY_CODEBASE_ROOT)
		hryky_emerg("HRYKY_CODEBASE_ROOT is not defined.")
	endif()
	
	find_package(Kmyacc)
	get_filename_component(grammar_name ${grammar} NAME)
	get_filename_component(grammar_name_we ${grammar} NAME_WE)
	KMYACC_COMMAND(
		${grammar} 
		${dest_dir} 
		${HRYKY_CODEBASE_ROOT}/etc/kmyacc.cpp.parser 
		${grammar_name_we}
		-l)
	set(output_grammar ${dest_dir}/${grammar_name}.h)
	
	# renames the extension of the output from .tab.c to .h
	add_custom_command(
		OUTPUT  ${output_grammar}
		COMMAND ${CMAKE_COMMAND} 
		ARGS 
			-E copy
			${dest_dir}/${grammar_name_we}.tab.c
			${output_grammar}
		DEPENDS ${dest_dir}/${grammar_name_we}.tab.c
		COMMENT "rename ${grammar_name_we}.tab.c to ${grammar_name}.h."
		VERBATIM)
	add_dependencies(${PROJECT_NAME} ${output_grammar})
endfunction()

#-------------------------------------------------------------------------------
# generates a directory
# param : {string} directory is the path to the generated directory.
#-------------------------------------------------------------------------------
function(hryky_make_directory directory)
	add_custom_command(
		OUTPUT ${directory}
		COMMAND ${CMAKE_COMMAND}
		ARGS -E make_directory ${directory}
		COMMENT "creates ${directory}"
		VERBATIM)
endfunction()

#-------------------------------------------------------------------------------
# copy a file
# param : {string} from is the path to the copied file.
# param : {string} to is the path to which the file will be copied.
#-------------------------------------------------------------------------------
function(hryky_copy_file from to)
	add_custom_command(
		OUTPUT ${to}
		COMMAND ${CMAKE_COMMAND}
		ARGS -E copy ${from} ${to}
		DEPENDS ${from}
		COMMENT "copy ${from} to ${to}"
		VERBATIM)
endfunction()

#-------------------------------------------------------------------------------
# concatenates files
# param : {string} dest is the destination to which the sources are concatanated.
#-------------------------------------------------------------------------------
function(hryky_concat_file dest)
	foreach(path ${ARGN})
		get_filename_component(path ${path} ABSOLUTE)
		list(APPEND paths ${path})
	endforeach()

	hryky_debug("concat_srcs : ${paths}")
	add_custom_command(
		OUTPUT ${dest}
		COMMAND hryky_concat
		ARGS 
			${dest}
			${paths}
		DEPENDS ${paths}
		COMMENT "concatenates ${paths} to ${dest}"
		VERBATIM)
endfunction()

#-------------------------------------------------------------------------------
# appends a component for packing.
# param : {string} name is the name of a module. (e.g. ascii)
# param : {string} desc is the description of the module.
# param : {ARGN} optional arguments are the list of the modules on which this 
#   module depends. (e.g. pixel;opengl)
#-------------------------------------------------------------------------------
function(hryky_add_packed_component name desc)
	if (NOT HRYKY_MINIMUM_MODULES)
		hryky_emerg("HRYKY_MINIMUM_MODULES is not defined.")
	endif()

	list(FIND HRYKY_MINIMUM_MODULES ${name} index_of)
	
	if (NOT -1 EQUAL ${index_of})
		hryky_debug("packing : ${name} is packed as the default module.")
		cpack_add_component(hryky_${name}
			DISPLAY_NAME 
				"${name}"
			DESCRIPTION 
				"${desc}"
			REQUIRED
			GROUP 
				HRYKY_LIB_COMPONENTS
			INSTALL_TYPES 
				HRYKY_INSTALL_TYPE_ALL 
				HRYKY_INSTALL_TYPE_NO_EXTERNAL)
		return()
	endif()
	
	foreach(depend ${HRYKY_MINIMUM_MODULES})
		list(APPEND depends hryky_${depend})
	endforeach()
	
	foreach(depend ${ARGN})
		if (NOT ${name} STREQUAL ${depend})
			list(APPEND depends hryky_${depend})
		endif()
	endforeach()
	
	hryky_debug("packing : ${name} is packed with ${depends}")
	
	cpack_add_component(hryky_${name}
		DISPLAY_NAME
			"${name}"
		DESCRIPTION
			"${desc}"
		DEPENDS
			${depends}
		GROUP
			HRYKY_LIB_COMPONENTS
		INSTALL_TYPES 
			HRYKY_INSTALL_TYPE_ALL 
			HRYKY_INSTALL_TYPE_NO_EXTERNAL)
endfunction()

#-------------------------------------------------------------------------------
# installs the directories of the module.
#-------------------------------------------------------------------------------
function(hryky_install_module_directories)
	hryky_install_directory(include ./)
	hryky_install_directory(${CMAKE_CURRENT_BINARY_DIR}/include ./)
	
	hryky_install_directory(${HRYKY_PLATFORM_NAME}/include ./)
	hryky_install_directory(
		${CMAKE_CURRENT_BINARY_DIR}/${HRYKY_PLATFORM_NAME}/include ./)
endfunction()

#-------------------------------------------------------------------------------
# describes a variables
# param : {variable} name_var is the name of the described variable.
#-------------------------------------------------------------------------------
function(hryky_print_var name_var)
	hryky_debug("${name_var} : ${${name_var}}")
endfunction()

#-------------------------------------------------------------------------------
# appends compile flags to files
# param : {variable} files_var is the variable representing each path to 
#         the modified file.
# param : {string} flags_var is the variable of additional properties.
#-------------------------------------------------------------------------------
function(hryky_append_files_compile_flags files_var flags_var)
	foreach(file ${${files_var}})
		hryky_append_file_compile_flags(${file} ${${flags_var}})
	endforeach()
endfunction()

#-------------------------------------------------------------------------------
# appends compile flags to a file
# param : {string} file is the path to the modified file.
# param : {ARGN} optional arguments are the list of additional flags.
#-------------------------------------------------------------------------------
function(hryky_append_file_compile_flags file)
	foreach(flag ${ARGN})
		hryky_append_file_compile_flag(${file} ${flag})
	endforeach()
endfunction()

#-------------------------------------------------------------------------------
# appends a compiler flag to a file
# param : {string} file is the path to the modified file.
# param : {string} flag is an additional flag.
#-------------------------------------------------------------------------------
function(hryky_append_file_compile_flag file flag)
	get_source_file_property(prev ${file} COMPILE_FLAGS)
	if (NOT prev)
		set(prev "")
	endif()
	set_source_files_properties(
		${file}
		PROPERTIES
		COMPILE_FLAGS "${prev} ${flag}"
	)
	hryky_debug(
		"modifies preprocessor definitions of ${file}: ${prev} ${flag}")
endfunction()

#-------------------------------------------------------------------------------
# appends a preprocessor macro to a file
# param : {string} file is the path to the modified file.
# param : {ARGN} optional arguments are the list of additional preprocessor 
#   macros.
#-------------------------------------------------------------------------------
function(hryky_append_definitions file)
	get_source_file_property(prev_flags ${file} COMPILE_DEFINITIONS)
	if (NOT prev)
		set(prev "")
	endif()
	set_source_files_properties(${file}
		PROPERTIES
		COMPILE_DEFINITIONS "${prev} ${ARGN}"
	)
	hryky_debug(
		"modifies preprocessor definitions of ${file}: ${prev} ${ARGN}")
endfunction()

#-------------------------------------------------------------------------------
# applies the common definition for header only project.
#-------------------------------------------------------------------------------
function(hryky_build_header_module)
	hryky_debug("starts to configure a header module ${PROJECT_NAME} {")
	hryky_descend()

	hryky_init_project_variables()
	
	add_custom_target(${PROJECT_NAME} 
		COMMENT "${PROJECT_NAME} has no source file."
		VERBATIM)

	# registers the include directories for the examination by CppCheck.
	include_directories(
		include
		${CMAKE_CURRENT_BINARY_DIR}/include
		${CMAKE_CURRENT_BINARY_DIR}/kmyacc
		${HRYKY_EXTERNAL_DIR}
		
		${HRYKY_PLATFORM_NAME}/include
		${CMAKE_CURRENT_BINARY_DIR}/${HRYKY_PLATFORM_NAME}/include
		)
	hryky_use_module(${HRYKY_MINIMUM_MODULES})

	if (HRYKY_CODEBASE_INSTALL)
		hryky_install_module_directories()
	endif()

	hryky_ascend()
	hryky_debug("} ends to configure a header module ${PROJECT_NAME}")

endfunction()

#-------------------------------------------------------------------------------
# appends searched files recursively
# param : {variable} dest_var is the name of the destination variable.
# param : {string} exp is the search expression of list() function.
#-------------------------------------------------------------------------------
function(hryky_find_file_recurse dest_var exp)
	file(GLOB_RECURSE founds ${exp})
	list(APPEND ${dest_var} ${founds})
	hryky_export_var_quietly(${dest_var})
endfunction()

#-------------------------------------------------------------------------------
# appends searched files
# param : {variable} dest_var is the name of the destination variable.
# param : {string} exp is the search expression of list() function.
#-------------------------------------------------------------------------------
function(hryky_find_file dest_var exp)
	file(GLOB founds ${exp})
	list(APPEND ${dest_var} ${founds})
	hryky_export_var_quietly(${dest_var})
endfunction()

#-------------------------------------------------------------------------------
# initializes the variables for the current project.
#
# outputs the following variables to the parent scope.
#   {string} <PROJECT_NAME>_VERSION_MAJOR is the major version of this project.
#   {string} <PROJECT_NAME>_VERSION_MINOR is the minor version of this project.
#   {string} <PROJECT_NAME>_VERSION_PATH the patch version of this project.
#   {string} <PROJECT_NAME>_VERSION is the composite version of this project.
#-------------------------------------------------------------------------------
function(hryky_init_project_variables)

	set(${PROJECT_NAME}_VERSION_MAJOR 00
		CACHE STRING
		"the number of major version")
	set(${PROJECT_NAME}_VERSION_MINOR 00
		CACHE STRING
		"the number of minor version")
	set(${PROJECT_NAME}_VERSION_PATCH 04
		CACHE STRING
		"the number of patch version")
	set(${PROJECT_NAME}_VERSION 
		${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
		
	hryky_export_var(${PROJECT_NAME}_VERSION_MAJOR)
	hryky_export_var(${PROJECT_NAME}_VERSION_MINOR)
	hryky_export_var(${PROJECT_NAME}_VERSION_PATCH)
	hryky_export_var(${PROJECT_NAME}_VERSION)
endfunction()

#-------------------------------------------------------------------------------
# initializes common variables for all modules
#
# outputs the following variables to the parent scope.
#   {boolean}   HRYKY_INIT_COMMON_VARIABLES is the history of invocation.
#   {string}    HRYKY_PLATFORM_NAME is the identifier of the target platform.
#   {boolean}   HRYKY_BUILD_STATIC_LIB specifies whether a library is built as
#               a static library.
#   {boolean}   HRYKY_USE_STATIC_CRT specifies whether the static C runtime 
#               library is linked in Windows platform.
#   {boolean}   HRYKY_USE_EXCEPTION specifies whether the C++ Exception is used.
#               This variable is referred in C/C++ source codes through config.h.
#   {boolean}   HRYKY_ARCH64 specifies whether the target platform is 64bit.
#               This variable is referred in C/C++ source codes through config.h.
#   {string[]}  HRYKY_LIBRARY_PROJECTS is the list of built libraries.
#   {string[]}  HRYKY_MODULES is the list of the names of all modules.
#   {string[]}  HRYKY_MINIMUM_MODULES is the list of the names of prerequisites 
#               module.
#
#   The following variables are Windows only.
#   {string}    HRYKY_WINVER represents WINVER macro.
#               This variable is referred in C/C++ source codes through config.h.
#   {string}    HRYKY_WINNT represents _WIN32_WINNT macro.
#               This variable is referred in C/C++ source codes through config.h.
#   {string}    HRYKY_NTDDI_VERSION represents NTDDI_VERSION macro.
#               This variable is referred in C/C++ source codes through config.h.
#
#-------------------------------------------------------------------------------
function(hryky_init_common_variables)
	if (HRYKY_INIT_COMMON_VARIABLES)
		# return()
	endif()
	set(HRYKY_INIT_COMMON_VARIABLES true)

	hryky_debug("hryky_init_common_variables is called.")

	get_property(
		HRYKY_CALLSTACK 
		GLOBAL 
		PROPERTY HRYKY_CALLSTACK 
		DEFINED)
	if (HRYKY_CALLSTACK)
		define_property(
			GLOBAL
			PROPERTY HRYKY_CALLSTACK
			BRIEF_DOCS "callstack"
			FULL_DOCS "The hierarchical information of stackframes.")
		set_property(
			GLOBAL PROPERTY HRYKY_CALLSTACK "")
	endif()

	get_property(
		HRYKY_EXTERNALS 
		GLOBAL 
		PROPERTY HRYKY_EXTERNALS 
		DEFINED)
	if (HRYKY_EXTERNALS)
		define_property(
			GLOBAL
			PROPERTY HRYKY_EXTERNALS
			BRIEF_DOCS "The current modules"
			FULL_DOCS "The list of modules.")
		set_property(
			GLOBAL PROPERTY HRYKY_EXTERNALS "")
	endif()

	if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
		set(HRYKY_PLATFORM_NAME "win32")
		hryky_debug("The target platform is Windows.")
		set(hryky_concat "type")
	elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(HRYKY_PLATFORM_NAME "linux")
		hryky_debug("The target platform is Linux.")
		set(hryky_concat "cat")
	else()
		hryky_emerg("This platform is not supported: ${CMAKE_SYSTEM_NAME}")
	endif()
	
	set(HRYKY_BUILD_STATIC_LIB ON
		CACHE BOOL "whether hryky-codebase library is built as static library")
	set(HRYKY_USE_STATIC_CRT ON
		CACHE BOOL
		"whether C Runtime Library is linked as static library")
		
	set(HRYKY_USE_EXCEPTION 1
		CACHE BOOL "whether main function is enclosed by try-catch statement")
		
	set(HRYKY_USE_VARIADIC_TEMPLATE 0
		CACHE BOOL "The use of variadic template of C++11")

	set(HRYKY_USE_STD_RESULT_OF 1
		CACHE BOOL "The use of std::result_of<>")

	if (MSVC AND (MSVC_VERSION LESS 1800))
		set(support_deleted_function 0)
	else()
		set(support_deleted_function 1)
	endif()
	set(HRYKY_SUPPORT_DELETED_FUNCTION ${support_deleted_function}
		CACHE BOOL "The compiler supports to 'delete' definition")
		
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(arch64 1)
	else()
		set(arch64 0)
	endif()
	set(HRYKY_ARCH64 ${arch64}
		CACHE BOOL "wether the architecture of target platform is 64bit.")

	#---------------------------------------
	# built libraries.
	# When a new library is created, this list has to be updated.
	#---------------------------------------
	set(libraries
		ascii
		chrono
		clock
		container
		core
		date
		debug
		display 
		error
		event
		exclusion
		file
		flow
		framework
		http
		ip
		json
		kademlia
		log
		memory
		openal
		opengl
		path
		pixel
		mempool
		sdl
		shader
		socket
		ssl
		task
		testing
		thread
		type
		uri
		window
		writer
		)
		
	if (WIN32)
		list(APPEND libraries win32)
	endif()
	
	foreach(library ${libraries})
		list(APPEND HRYKY_LIBRARY_PROJECTS hryky_${library})
	endforeach()
	
	#---------------------------------------
	# header-only modules.
	# When a new header-only module is created, this list has to be updated.
	#---------------------------------------
	set(HRYKY_MODULES 
		${libraries}
		accumulator
		allocator
		atomic
		batch
		bignum
		coord
		feature
		functional
		geometry
		iterator
		linear_algebra 
		permutation
		profiler
		random
		runnable
		stream
		streambuf
		symbolic_computation
		tmp
		tuple
		type_traits
		utf16
		utf8
		vector_space
		)
	
	#---------------------------------------
	# prerequisites modules.
	# When a module is required by all other modules, this list has to be 
	# updated.
	#---------------------------------------
	set(HRYKY_MINIMUM_MODULES
		allocator 
		atomic 
		container 
		core 
		debug 
		exclusion 
		feature 
		file
		functional
		iterator 
		json 
		linear_algebra 
		log 
		memory 
		mempool 
		path
		stream 
		streambuf 
		tmp 
		tuple 
		type 
		type_traits 
		utf16
		utf8
		vector_space
		)
		
	if (WIN32)
		list(APPEND HRYKY_MINIMUM_MODULES win32)
	endif()
	
	if (WIN32)
		add_definitions(
			-DHRYKY_PLATFORM_WINDOWS=1
			-DHRYKY_PLATFORM_POSIX=0
			-DWIN32_LEAN_AND_MEAN)
	elseif (UNIX)
		add_definitions(
			-DHRYKY_PLATFORM_WINDOWS=0
			-DHRYKY_PLATFORM_POSIX=1)
	endif()
	
	if (MSVC)
		add_definitions(
			-Wall -WX 
			-wd4514 -wd4820 -wd4061 -wd4710 -wd4350 -wd4503)
	endif()

	# initializes c/c++ compiler flags
	set(cxx_flags_vars_debug
		CMAKE_CXX_FLAGS_DEBUG 
		CMAKE_C_FLAGS_DEBUG 
		CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_C_FLAGS_RELWITHDEBINFO)
	set(cxx_flags_vars_release
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_C_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_MINSIZEREL
		CMAKE_C_FLAGS_MINSIZEREL)
	set(cxx_flags_vars 
		${cxx_flags_vars_debug}
		${cxx_flags_vars_release})
		
	# sets up flags to use exception
	if (MSVC)
		if (HRYKY_USE_EXCEPTION)
			set(exception_flag_debug "/EHsc"
				CACHE STRING 
				"compiler flag for handling C++ exception at Debug Configuration")
				
			foreach(flags_var ${cxx_flags_vars_debug})
				set(${flags_var} "${${flags_var}} ${exception_flag_debug}")
			endforeach()
			
			set(exception_flag_release "/EHsc"
				CACHE STRING 
				"compiler flag for handling C++ exception at Release Configuration")
				
			foreach(flags_var ${cxx_flags_vars_release})
				set(${flags_var} "${${flags_var}} ${exception_flag_release}")
			endforeach()
		endif()
	endif()

	# forces to use static C-runtime library.
	# CMake for MSVC uses DLL in default configuration.
	# http://stackoverflow.com/questions/1618927/cmake-microsoft-visual-studio-and-monolithic-runtimes
	if(MSVC)
		if (HRYKY_USE_STATIC_CRT)
			foreach(flags_var ${cxx_flags_vars})
				set(dest ${flags_var})
				set(src ${${flags_var}})
				if(${src} MATCHES "/MD")
					string(REGEX REPLACE "/MD" "/MT" ${dest} "${src}")
				endif()
				if(${src} MATCHES "/MDd")
					string(REGEX REPLACE "/MDd" "/MTd" ${dest} "${src}")
				endif()
			endforeach()
		endif()
	endif()

	if(MSVC)
		foreach(flags_var ${cxx_flags_vars})
			# ignores warnings
			set(${flags_var} "${${flags_var}} /wd4819")
			# displays an absolute path where an error occurs.
			set(${flags_var} "${${flags_var}} /FC")
			# enables the parallel compilation.
			set(${flags_var} "${${flags_var}} /MP")
			# prints the hierarchy of include files.
			# set(${flags_var} "${${flags_var}} /showIncludes")
		endforeach()
		# ingnores the warning for using unsafe functions (e.g. sprintf)
		add_definitions(-D_SCL_SECURE_NO_WARNINGS)
		# ignores the warning to disable deprecated API warnings.
		add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
	endif()

	# configuration for OS version
	if (MSVC)
		set(HRYKY_NTDDI_VERSION 0x06010000 
			CACHE STRING 
			"minimum requirement of the Windows OS version")
		string(SUBSTRING ${HRYKY_NTDDI_VERSION} 0 6 HRYKY_WINVER)
		string(SUBSTRING ${HRYKY_NTDDI_VERSION} 0 6 HRYKY_WINNT)
	endif()

	hryky_export_var(HRYKY_INIT_COMMON_VARIABLES)
	hryky_export_var(HRYKY_PLATFORM_NAME)
	hryky_export_var(HRYKY_BUILD_STATIC_LIB)
	hryky_export_var(HRYKY_USE_STATIC_CRT)
	hryky_export_var(HRYKY_USE_EXCEPTION)
	hryky_export_var(HRYKY_ARCH64)
	hryky_export_var(HRYKY_LIBRARY_PROJECTS)
	hryky_export_var(HRYKY_MODULES)
	hryky_export_var(HRYKY_MINIMUM_MODULES)

	if (MSVC)
		hryky_export_var(HRYKY_WINVER)
		hryky_export_var(HRYKY_WINNT)
		hryky_export_var(HRYKY_NTDDI_VERSION)

		# exports the modified compiler flags
		foreach(flags ${cxx_flags_vars})
			hryky_export_var(${flags})
		endforeach()
	endif()

endfunction()

#-------------------------------------------------------------------------------
# inserts the common setting to build the module as library.
#
# options:
#  If HRYKY_PCH_SOURCE is defined, the value is used as the source file which
# the precompiled header is based on.
#-------------------------------------------------------------------------------
function(hryky_build_library)
	hryky_debug("starts to configure a library ${PROJECT_NAME} {")
	hryky_descend()
	
	hryky_init_project_variables()
	
	# collects built sources.
	hryky_find_file_recurse(cpp_sources src/*.cpp)

	# appends the source files for the target platform.
	hryky_find_file_recurse(cpp_sources ${HRYKY_PLATFORM_NAME}/src/*.cpp)
	
	# uses precompilation
	if (DEFINED HRYKY_PCH_SOURCE)
		hryky_use_precompiled_header(
			precompiled.h ${HRYKY_PCH_SOURCE} cpp_sources)
	endif()
		
	# requests to build the library.
	hryky_append_built_library(${PROJECT_NAME} ${cpp_sources})

	hryky_use_boost()

	include_directories(
		src
		include
		${CMAKE_CURRENT_BINARY_DIR}/include
		${CMAKE_CURRENT_BINARY_DIR}/kmyacc
		${HRYKY_EXTERNAL_DIR}
		
		# appends include directories for the target platform.
		${HRYKY_PLATFORM_NAME}/src
		${HRYKY_PLATFORM_NAME}/include
		${CMAKE_CURRENT_BINARY_DIR}/${HRYKY_PLATFORM_NAME}/include
		)
		
	if (NOT HRYKY_MINIMUM_MODULES)
		hryky_emerg("HRYKY_MINIMUM_MODULES is not defined.")
	endif()
	hryky_use_module(${HRYKY_MINIMUM_MODULES})
	
	if (HRYKY_BUILD_STATIC_LIB)
		if (HRYKY_CODEBASE_INSTALL)
			install(TARGETS ${PROJECT_NAME}
				ARCHIVE
				DESTINATION lib
				COMPONENT ${PROJECT_NAME}
				)
		endif()
	else()
		install(TARGETS ${PROJECT_NAME} 
			DESTINATION lib
			COMPONENT ${PROJECT_NAME}
			)
	endif()

	if (HRYKY_CODEBASE_INSTALL)
		hryky_install_module_directories()
	endif()

	hryky_ascend()
	hryky_debug("} ends to configure a library ${PROJECT_NAME}")

endfunction()

#-------------------------------------------------------------------------------
# inserts common definition for an executable project.
#
# options:
#  If HRYKY_PCH_SOURCE is defined, the value is used as the source file which
# the precompiled header is based on.
#-------------------------------------------------------------------------------
function(hryky_build_executable)
	hryky_debug("starts to configure an executable ${PROJECT_NAME} {")
	hryky_descend()
	
	hryky_init_project_variables()
	
	# collects built sources.
	hryky_find_file_recurse(cpp_sources src/*.cpp)

	# appends the source files for the target platform.
	hryky_find_file_recurse(cpp_sources ${HRYKY_PLATFORM_NAME}/src/*.cpp)

	# uses precompilation
	if (DEFINED HRYKY_PCH_SOURCE)
		hryky_use_precompiled_header(
			precompiled.h ${HRYKY_PCH_SOURCE} cpp_sources)
	endif()
		
	# requests to build the executable.
	add_executable(${PROJECT_NAME} ${HRYKY_PCH_SOURCE} ${cpp_sources})
	
	hryky_use_boost()

	include_directories(
		src
		include
		${CMAKE_CURRENT_BINARY_DIR}/include
		${CMAKE_CURRENT_BINARY_DIR}/kmyacc
		${HRYKY_EXTERNAL_DIR}
		
		# appends include directories for the target platform.
		${HRYKY_PLATFORM_NAME}/src
		${HRYKY_PLATFORM_NAME}/include
		${CMAKE_CURRENT_BINARY_DIR}/${HRYKY_PLATFORM_NAME}/include
		)

	hryky_ascend()
	hryky_debug("} ends to configure the executable ${PROJECT_NAME}")

endfunction()

#-------------------------------------------------------------------------------
# creates the configuration header
#-------------------------------------------------------------------------------
function(hryky_configure_header)
	if (HRYKY_ARCH64)
		set(arch64 1)
	else()
		set(arch64 0)
	endif()
	
	if (HRYKY_USE_EXCEPTION)
		set(use_exception 1)
	else()
		set(use_exception 0)
	endif()
	
	if (HRYKY_USE_VARIADIC_TEMPLATE)
		set(use_variadic_template 1)
	else()
		set(use_variadic_template 0)
	endif()
	
	if (HRYKY_USE_STD_RESULT_OF)
		set(use_std_result_of 1)
	else()
		set(use_std_result_of 0)
	endif()
	
	if (HRYKY_SUPPORT_DELETED_FUNCTION)
		set(support_deleted_function 1)
	else()
		set(support_deleted_function 0)
	endif()
	
	configure_file(
		${HRYKY_CONFIG_IN}
		${CMAKE_CURRENT_BINARY_DIR}/include/hryky/config.h)
endfunction()

#-------------------------------------------------------------------------------
# increments stackframes
#-------------------------------------------------------------------------------
function(hryky_descend)
	hryky_get_callstack(callstack)
	string(RANDOM id)
	list(APPEND callstack "${id}")
	hryky_set_callstack(${callstack})

	set(delimiter)
	list(LENGTH callstack length)
	while(length)
		list(GET callstack 0 stackframe)
		list(APPEND delimiter "${stackframe}{")
		list(REMOVE_AT callstack 0)
		list(LENGTH callstack length)
	endwhile()
	hryky_debug(${delimiter})
endfunction()

#-------------------------------------------------------------------------------
# decrements stackframes
#-------------------------------------------------------------------------------
function(hryky_ascend)
	hryky_get_callstack(callstack)
	set(delimiter)
	list(LENGTH callstack length)
	while(length)
		list(GET callstack -1 stackframe)
		list(APPEND delimiter "}${stackframe}")
		list(REMOVE_AT callstack -1)
		list(LENGTH callstack length)
	endwhile()
	hryky_debug(${delimiter})

	hryky_get_callstack(callstack)
	hryky_pop(callstack)
	hryky_set_callstack(${callstack})
endfunction()

#-------------------------------------------------------------------------------
# removes the last element of list.
#-------------------------------------------------------------------------------
function(hryky_pop var_name)
	list(REMOVE_AT ${var_name} -1)
	hryky_export_var_quietly(${var_name})
endfunction()

#-------------------------------------------------------------------------------
# starts to use an external module.
#-------------------------------------------------------------------------------
function(hryky_begin_external external)
	get_property(externals GLOBAL PROPERTY HRYKY_EXTERNALS)
	list(APPEND externals ${external})
	set_property(
		GLOBAL PROPERTY HRYKY_EXTERNALS ${externals})
	
	hryky_debug("starts to use ${external} for ${PROJECT_NAME} {")
	hryky_descend()
endfunction()

#-------------------------------------------------------------------------------
# ends to use the external module.
#-------------------------------------------------------------------------------
function(hryky_end_external)
	get_property(externals GLOBAL PROPERTY HRYKY_EXTERNALS)
	list(GET externals -1 external)
	hryky_pop(externals)
	set_property(
		GLOBAL PROPERTY HRYKY_EXTERNALS ${externals})

	hryky_ascend()
	hryky_debug("} ends to use ${external} for ${PROJECT_NAME}")
endfunction()

#------------------------------------------------------------------------------
# retrieves the callstack
#------------------------------------------------------------------------------
function(hryky_get_callstack var_name)
	get_property(${var_name} GLOBAL PROPERTY HRYKY_CALLSTACK)
	hryky_export_var_quietly(${var_name})
endfunction()

#------------------------------------------------------------------------------
# assign a new value to the callstack
#------------------------------------------------------------------------------
function(hryky_set_callstack)
	set_property(
		GLOBAL PROPERTY HRYKY_CALLSTACK ${ARGV})
endfunction()

#------------------------------------------------------------------------------
# prints the message
#------------------------------------------------------------------------------
function(hryky_print level)
	hryky_get_callstack(callstack)
	set(prefix)
	list(LENGTH callstack length)
	while(${length})
		list(APPEND prefix "  ")
		math(EXPR length "${length}-1")
	endwhile()
	if (0 EQUAL level)
		message(STATUS "${prefix}${ARGN}")
	elseif (1 EQUAL level)
		message("${prefix}${ARGN}")
	elseif (2 EQUAL level)
		message(WARNING "${prefix}${ARGN}")
	elseif (3 EQUAL level)
		message(AUTHOR_WARNING "${prefix}${ARGN}")
	elseif (4 EQUAL level)
		message(SEND_ERROR "${prefix}${ARGN}")
	else()
		message(FATAL_ERROR "${prefix}${ARGN}")
	endif()
endfunction()

#------------------------------------------------------------------------------
# prints a debugging information
#------------------------------------------------------------------------------
function(hryky_debug)
	hryky_print(0 ${ARGV})
endfunction()

#------------------------------------------------------------------------------
# prints a warning message
#------------------------------------------------------------------------------
function(hryky_warn)
	hryky_print(2 ${ARGV})
endfunction()

#------------------------------------------------------------------------------
# prints an emergent message
#------------------------------------------------------------------------------
function(hryky_emerg)
	hryky_print(5 ${ARGV})
endfunction()

#-------------------------------------------------------------------------------
# macros
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# defines the variables to create an installer.
#-------------------------------------------------------------------------------
macro(hryky_include_pack)
	include(InstallRequiredSystemLibraries)
	
	set(CPACK_RESOURCE_FILE_LICENSE     ${CMAKE_SOURCE_DIR}/LICENSE.txt)
	set(CPACK_PACKAGE_NAME              ${PROJECT_NAME})
	set(CPACK_PACKAGE_VENDER            hryky)
	# set(CPACK_PACKAGE_EXECUTABLES)
	set(CPACK_PACKAGE_VERSION           ${${PROJECT_NAME}_VERSION})
	set(CPACK_PACKAGE_VERSION_MAJOR     ${${PROJECT_NAME}_VERSION_MAJOR})
	set(CPACK_PACKAGE_VERSION_MINOR     ${${PROJECT_NAME}_VERSION_MINOR})
	set(CPACK_PACKAGE_VERSION_PATCH     ${${PROJECT_NAME}_VERSION_PATCH})
	set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
	
	include(CPack)
endmacro()

#-------------------------------------------------------------------------------
# defines a variable in the parent scope
# param : {string} name is the name of a variable.
#-------------------------------------------------------------------------------
macro(hryky_export_var name)
	hryky_export_var_quietly(${name})
	hryky_debug("exports ${name} : ${${name}}")
endmacro()

#-------------------------------------------------------------------------------
# defines a variable in the parent scope quietly
# param : {string} name is the name of a variable.
#-------------------------------------------------------------------------------
macro(hryky_export_var_quietly name)
	set(${name} ${${name}} PARENT_SCOPE)
endmacro()

#-------------------------------------------------------------------------------
# actions
#-------------------------------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH ${HRYKY_CODEBASE_ROOT}/etc)
set(HRYKY_CONFIG_IN ${HRYKY_CODEBASE_ROOT}/etc/config.h.in)
set(HRYKY_EXTERNAL_DIR ${HRYKY_CODEBASE_ROOT}/external)

#-------------------------------------------------------------------------------
# defines common variables among the target platform.
#-------------------------------------------------------------------------------
hryky_init_common_variables()
