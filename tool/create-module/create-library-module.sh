#!/bin/sh
#-------------------------------------------------------------------------------
# brief:
#   create a new libary module under lib/ directory
# usage:
#   create-library-module.sh MODULENAME
#       MODULENAME is the name of new module.
# version:
#   $Id: create-library-module.sh 313 2014-01-21 09:42:50Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------

module_name=$1
script_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cmake_lists=$script_root/CMakeLists.txt.template
library_module_cmake=$script_root/library-module.cmake.template
precompiled_cpp=$script_root/library-module.precompiled.cpp.template
precompiled_h=$script_root/library-module.precompiled.h.template
precompiled_h_date=`date +%Y%m%d%H%M%S%N`
lib_root=$DEVROOT/hryky-codebase/lib

if [ ! -f "$cmake_lists" ]; then
	echo ERROR: "$cmake_lists" is not found.
	exit 1
fi

if [ ! -f "$library_module_cmake" ]; then
	echo ERROR: "$library_module_cmake" is not found.
	exit 1
fi

if [ ! -f "$precompiled_cpp" ]; then
	echo ERROR: "$precompiled_cpp" is not found.
	exit 1
fi

if [ ! -f "$precompiled_h" ]; then
	echo ERROR: "$precompiled_h" is not found.
	exit 1
fi

if [ ! -d "$lib_root" ]; then
	echo ERROR: "$lib_root" is not found.
	exit 1
fi

pushd $lib_root

mkdir -v $module_name

pushd $module_name

cp -v $cmake_lists ./CMakeLists.txt
sed -i "s/<module_name>/${module_name}/g" CMakeLists.txt

cp -v $library_module_cmake ./$module_name.cmake
sed -i "s/<module_name>/${module_name}/g" ./$module_name.cmake

mkdir -v -p include/hryky/$module_name
mkdir -v -p src

cp -v $precompiled_cpp src/$module_name.cpp
sed -i "s/<module_name>/${module_name}/g" src/$module_name.cpp

cp -v $precompiled_h src/precompiled.h
sed -i "s/<module_name>/${module_name}/g" src/precompiled.h
sed -i "s/<date>/${precompiled_h_date}/g" src/precompiled.h

exit 0