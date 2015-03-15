cmake_minimum_required(VERSION 2.8.10.2)

project(OpenAL)

set(FORCE_STATIC_VCRT ON)

add_subdirectory(
	../../../../openal-soft
	${CMAKE_CURRENT_BINARY_DIR}/openal-soft)

