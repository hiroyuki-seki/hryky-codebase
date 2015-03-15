#!/bin/sh
#------------------------------------------------------------------------------
# brief:
#   renames multiple files controlled under Subversion.
# usage:
#   svn-rename.sh SRCDIR SRCMODULE DESTMODULE
#       SRCDIR is the directory retainning renamed files.
#       SRCMODULE is the word to be replaced.
#       DESTMODULE is the substituted word.
# version:
#   $Id: svn-rename.sh 253 2013-10-27 05:06:41Z hryky.private@gmail.com $
#------------------------------------------------------------------------------

SRCDIR=$1
SRCMODULE=$2
DESTMODULE=$3

if [ ! -d "$SRCDIR" ]; then
    echo The source directory "$SRCDIR" is not found.
    exit 1
fi

for file in `find $SRCDIR -regex .*$SRCMODULE.*`
do
    svn rename ${file} ${file/$SRCMODULE/$DESTMODULE}
done

exit 0
