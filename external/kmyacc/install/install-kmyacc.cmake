#-------------------------------------------------------------------------------
# file:
#   CMakeLists.txt
# brief:
#   builds kmyacc by CMake
# version:
#   $Id: install-kmyacc.cmake 339 2014-03-25 06:00:27Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
project(kmyacc)

if(NOT KMYACC_SOURCE_DIR)
	set(KMYACC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../kmyacc-4.1.4)
endif()
message(STATUS "KMYACC_SOURCE_DIR is ${KMYACC_SOURCE_DIR}")

if(MSVC)
	set (CMAKE_MFC_FLAG 0)
	set (CMAKE_INSTALL_MFC_LIBRARIES 0)
	foreach(configuration ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${configuration} configuration)
		set(flags CMAKE_C_FLAGS_${configuration})
		string(
			REGEX REPLACE "/MD" "/MT" ${flags} "${${flags}}")
		string(
			REGEX REPLACE "/MDd" "/MTd"  ${flags} "${${flags}}")
		message(STATUS "${flags} is ${${flags}}")
	endforeach()
endif()

set(KMYACC_VERSION_MAJOR 4)
set(KMYACC_VERSION_MINOR 1)
set(KMYACC_VERSION_PATCH 4)
set(KMYACC_VERSION ${KMYACC_VERSION_MAJOR}.${KMYACC_VERSION_MINOR}.${KMYACC_VERSION_PATCH})

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_definitions(-DHAS_STLIB)

include_directories(${KMYACC_SOURCE_DIR}/src)

foreach(source yacc.c grammar.c token.c lalr.c genparser.c compress.c misc.c)
	list(APPEND kmyacc_sources ${KMYACC_SOURCE_DIR}/src/${source})
endforeach()
message(STATUS "kmyacc_sources are ${kmyacc_sources}")
add_executable(kmyacc ${kmyacc_sources})

file(GLOB kmyacc_parsers 
	${KMYACC_SOURCE_DIR}/src/*.parser)

install(TARGETS kmyacc RUNTIME DESTINATION bin)
install(FILES ${kmyacc_parsers}
	DESTINATION lib)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE     ${KMYACC_SOURCE_DIR}/COPYING)
set(CPACK_RESOURCE_FILE_README      ${KMYACC_SOURCE_DIR}/README)
set(CPACK_PACKAGE_NAME              kmyacc)
set(CPACK_PACKAGE_INSTALL_DIRECTORY kmyacc)
set(CPACK_PACKAGE_VERSION           ${KMYACC_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR     ${KMYACC_VERSION_MAJOR})
set(CPAck_PACKAGE_VERSION_MINOR     ${KMYACC_VERSION_MINOR})
set(CPAck_PACKAGE_VERSION_PATCH     ${KMYACC_VERSION_PATCH})

include(CPack)
