cmake_minimum_required(VERSION 2.8.10.2)

project(googletest)

add_subdirectory(
	../../../../googletest
	${CMAKE_CURRENT_BINARY_DIR}/googletest)
	
foreach(configuration ${CMAKE_CONFIGURATION_TYPES})
	get_target_property(gtest_location gtest LOCATION_${configuration})
	get_target_property(gtest_main_location gtest_main LOCATION_${configuration})
	
	install(FILES 
		${gtest_location}
		${gtest_main_location}
		DESTINATION lib/${configuration}
		CONFIGURATIONS ${configuration}
		OPTIONAL)
endforeach()

install(DIRECTORY ${gtest_SOURCE_DIR}/include
	DESTINATION ./
	PATTERN "*.h")
