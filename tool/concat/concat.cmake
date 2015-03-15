#-------------------------------------------------------------------------------
# file:
#   concat.cmake
# brief:
#   builds executable for concatenation
# version:
#   $Id: CMakeLists.txt 124 2012-12-29 05:48:12Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
project(hryky_concat)

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(WIN32)
	set(SEPARATOR "\\")
else()
	set(SEPARATOR "/")
endif()

set(VENDOR "hryky")

string(
	REPLACE 
	${PROJECT_NAME} "${VENDOR}/${PROJECT_NAME}" 
	CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
message(STATUS "CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")

add_executable(
	${PROJECT_NAME}
	src/hryky_concat.cpp)
	
if (HRYKY_CODEBASE_INSTALL)
	#-------------------------------------------------------------------------------
	# installation settings
	#-------------------------------------------------------------------------------
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin
		COMPONENT hryky_concat)
	
	#-------------------------------------------------------------------------------
	# creates installer
	#-------------------------------------------------------------------------------
	include(InstallRequiredSystemLibraries)
	
	string(
		REPLACE "${VENDOR}/${PROJECT_NAME}" "${VENDOR}" 
		CPACK_NSIS_INSTALL_ROOT ${CMAKE_INSTALL_PREFIX})
	string(
		REPLACE "/" "\\\\" 
		CPACK_NSIS_INSTALL_ROOT ${CPACK_NSIS_INSTALL_ROOT})
	
	set(CPACK_RESOURCE_FILE_LICENSE     ${CMAKE_SOURCE_DIR}/LICENSE.txt)
	set(CPACK_PACKAGE_NAME              ${PROJECT_NAME})
	set(CPACK_PACKAGE_VENDER            ${VENDOR})
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "concatenate files")
	set(CPACK_PACKAGE_VERSION_MAJOR     1)
	set(CPACK_PACKAGE_VERSION_MINOR     0)
	set(CPACK_PACKAGE_VERSION_PATCH     0)
	set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
	
	include(CPack)
endif()
