#!/bin/sh
#-------------------------------------------------------------------------------
# brief:
#   create a new header-only module under lib/ directory
# usage:
#   create-header-module.sh MODULENAME
#       MODULENAME is the name of new module.
# version:
#   $Id: create-header-module.sh 313 2014-01-21 09:42:50Z hryky.private@gmail.com $
#-------------------------------------------------------------------------------

module_name=$1
script_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cmake_lists=$script_root/CMakeLists.txt.template
header_module_cmake=$script_root/header-module.cmake.template
lib_root=$DEVROOT/hryky-codebase/lib

if [ ! -f "$cmake_lists" ]; then
	echo ERROR: "$cmake_lists" is not found.
	exit 1
fi

if [ ! -f "$header_module_cmake" ]; then
	echo ERROR: "$header_module_cmake" is not found.
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

cp -v $header_module_cmake ./$module_name.cmake
sed -i "s/<module_name>/${module_name}/g" ./$module_name.cmake

mkdir -v -p include/hryky/$module_name

exit 0