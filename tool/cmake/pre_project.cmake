#----------------------------------------------------------------
# brief:
#   Utility functions and macros for CMake.
#   include this file before 'project()'
# $Id$
#----------------------------------------------------------------

string(REGEX REPLACE "\\\\" "/" MSSDK $ENV{MSSDK})

#--------------------------------
# brief:
#   override default FLAGS.
#--------------------------------
set(CMAKE_USER_MAKE_RULES_OVERRIDE
   $ENV{DEVROOT}/working_copy/tool/cmake/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
   $ENV{DEVROOT}/working_copy/tool/cmake/cxx_flag_overrides.cmake)

