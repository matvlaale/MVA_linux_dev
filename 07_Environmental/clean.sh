#!/bin/bash

# autoreconf -i && ./configure --with-readline && make

rm -f aclocal.m4 compile config.log config.status configure depcomp install-sh
rm -f configure~ Makefile Makefile.in missing rhasher rhasher.o
rm -rf autom4te.cache .deps
