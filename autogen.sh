#!/bin/sh
mkdir -p m4
libtoolize --force --copy
aclocal --force --install
autoheader
automake --add-missing --copy
autoconf
