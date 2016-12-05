#!/bin/sh

if ! pushd "$DEVROOT/SDL"; then
	echo failed to move to "$DEVROOT/SDL".
	exit 1
fi

OLD_VER=${OLD_VER:-2013}
NEW_VER=${NEW_VER:-2015}

find . -type f \
	-regex '.*'${OLD_VER}'\.\(vcxproj\|sln\|vcxproj\.filters\)' \
	| awk '{old=$1;gsub(/'${OLD_VER}'/,"'${NEW_VER}'");print "cp -f -v",old,$1;}' \
	| sh

find . -type f \
	-regex '.*'${NEW_VER}'\.\(sln\)' \
	| xargs sed -i \
		-e 's/'${OLD_VER}'\.vcxproj/'${NEW_VER}'\.vcxproj/g' \
		-e 's/Visual Studio '${OLD_VER}'/Visual Studio '${NEW_VER}'/g'

find . -type f \
	-regex '.*'${NEW_VER}'\.\(sln\)' \
	| xargs unix2dos

find . -type f \
	-regex '.*'${NEW_VER}'\.\(vcxproj\)' \
	| xargs sed -i \
		-e 's/<PlatformToolset>v120</<PlatformToolset>v140</g' \
		-e 's/<RuntimeLibrary>MultiThreadedDebugDLL</<RuntimeLibrary>MultiThreadedDebug</g' \
		-e 's/<RuntimeLibrary>MultiThreadedDLL</<RuntimeLibrary>MultiThreaded</g' \
		-e 's/<ConfigurationType>DynamicLibrary</<ConfigurationType>StaticLibrary</g' \

find . -type f \
	-regex '.*'${NEW_VER}'\.\(vcxproj\)' \
	| xargs unix2dos

