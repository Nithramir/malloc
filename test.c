#include "malloc_src/malloc.h"

// int main() 
// { 
// int i; 
// char *addr; 

// i = 0; 
// while (i < 1024)
// { 
// 	addr = (char*)malloc(1024);
// 	addr[0] = 42;
// 	free(addr);
// 	i++; 
// } 
// 	// show_alloc_mem();

// return (0); 
// }


// #define M (1024 * 1024) 

// void print(char *s)
// { 
// write(1, s, strlen(s)); 
// } 

// int main() 
// { 
// char *addr1; 
// char *addr3; 

// addr1 = (char*)malloc(16*M); 
// strcpy(addr1, "Bonjours\n"); 
// print(addr1); 
// addr3 = (char*)realloc(addr1, 128*M); 
// addr3[127*M] = 42; 
// print(addr3); 
// return (0); 
// } 

// void print(char *s) 
// { 
// write(1, s, strlen(s)); 
// } 

// int main() 
// { 
// char *addr; 

// addr = malloc(16); 
// free(NULL); 
// free((void *)addr + 5); 
// if (realloc((void *)addr + 5, 10) == NULL) 
// print("Bonjours\n"); 
// } 

int main() 
{ 
malloc(1024); 
malloc(1024 * 32); 
malloc(1024 * 1024); 
malloc(1024 * 1024 * 16); 
malloc(1024 * 1024 * 128); 
show_alloc_mem(); 
return (0); 
} g