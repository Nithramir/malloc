#!/bin/sh 
export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES="malloc" 
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
#include "malloc_src/malloc.h"

int main() 
{ 
int i; 
char *addr; 

i = 0; 
while (i < 1024)
{ 
	addr = (char*)malloc(1024);
	addr[0] = 42;
	// free(addr);
	i++; 
} 
	// show_alloc_mem();

return (0); 
} 