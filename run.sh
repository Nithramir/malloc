#!/bin/sh 
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="malloc" 
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
