#-------------------------------------------------------------------------------
# file:
#   test.cmake
# brief:
#   tests hryky-codebase by CTest
# version:
#   $Id: test.cmake 357 2014-06-25 22:52:16Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------
add_subdirectory(test)

enable_testing()
file(GLOB HRYKY_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
hryky_print_var(HRYKY_TESTS)

foreach(test ${HRYKY_TESTS})
	get_filename_component(testname ${test} NAME_WE)
	string(REPLACE test_ "" testname ${testname})
	add_test(
		NAME ${testname} 
		COMMAND test_${PROJECT_NAME} ${testname})
	set_tests_properties(
		${testname}
		PROPERTIES PROCESSORS 1)
	message(STATUS "add test ${testname}")
endforeach()
