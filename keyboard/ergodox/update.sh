#!/bin/bash

# Blow the whole script up if any command fails
set -e

make -f Makefile.lufa clean
make -f Makefile.lufa
make -f Makefile.lufa teensy
