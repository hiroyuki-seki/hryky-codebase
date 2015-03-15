cmake_minimum_required(VERSION 2.8.10.2)

project(libpng)

set(PNG_STATIC true)
set(PNG_SHARED false)

if (WIN32)
	set(ZLIB_ROOT $ENV{ProgramW6432}/zlib $ENV{ProgramFiles}/zlib)
endif()

add_subdirectory(
	../../../../libpng
	${CMAKE_CURRENT_BINARY_DIR}/libpng)

