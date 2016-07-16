#!/bin/sh

echo -n "old chapter is: "; read src; echo $src
echo -n "new chapter is: "; read dest; echo $dest

if [ ! -d "$src" ]; then
  echo source directory ./$src/ is not found.
  exit 1
fi

mkdir ${dest}

cp -v ${src}/rtiow_${src}.cpp ${dest}/rtiow_${dest}.cpp
cp -v ${src}/Makefile.am ${dest}/
cp -v ${src}/configure.ac ${dest}/

sed -i "s/${src}/${dest}/g" ${dest}/Makefile.am
sed -i "s/${src}/${dest}/g" ${dest}/configure.ac

git add ${dest}
git add ${dest}/Makefile.am
git add ${dest}/configure.ac

pushd ${dest}
aclocal
autoconf
automake -a
./configure
make

exit 0
