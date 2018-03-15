
#ifndef MALLOC_H
#define MALLOC_H
#include "../libft/libft/libft.h"
#include <sys/mman.h>
#define MALLOC_TINY getpagesize()
#define MALLOC_SMALL getpagesize() * 64

/*
** describe a allocated zone
*/
typedef struct s_allocated {
    size_t      size;
    void        *position;
}               t_allocated;

/*
** List of allocated zone
*/
typedef struct  s_mem_zone {
    void                *mem_zone;
    t_allocated         *list_malloc;
    size_t              list_malloc_size;
    size_t              memory_size;
    size_t              memory_used;
    struct s_mem_zone   *next;
    struct s_mem_zone   *before;
}               t_mem_zone;

/*
** Main struct with pointer on different malloc list
*/
typedef struct  s_malloc {
    t_mem_zone *tiny;
    t_mem_zone *small;
    t_mem_zone *large;
    void        *list_mem_zone;
    void        *list_allocated;
}               t_malloc;

t_mem_zone *new_mem_zone(size_t size, t_mem_zone *before);
void *add_malloc(t_mem_zone *zone, size_t asked_memory_size);
t_mem_zone *get_memory_place(t_mem_zone *zone, size_t asked_memory_size, size_t zone_size);
void *get_memory(size_t size);
int ft_search_ptr(void *ptr, t_mem_zone **zone);
void defragmentation(t_mem_zone *zone);
void clean_zone(t_mem_zone *zone, size_t pos, t_mem_zone **first_zone);
size_t ft_search_size(void *ptr, t_mem_zone *first_zone);
#endif