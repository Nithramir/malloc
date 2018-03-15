#include "malloc.h"

void *get_memory(size_t size) {
    char *mem;
    size_t i = 0;

    ft_printf("Asked memory: %zu\n", size);
    mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON |MAP_PRIVATE, -1, 0);
    // mem = malloc(size);
    while (i < size) {
        mem[i] = '\0';
        i++;
    }
    return mem;
}

void ft_copy(char *dest, char *src, size_t n) {
    size_t i;

    i = 0;
    while (i < n) {
        dest[i] = src[i];
        i++;
    }
}

t_allocated *set_bigger_list_malloc(t_mem_zone *zone) {
    size_t new_list_malloc_size = zone->list_malloc_size + 256;
    t_allocated *new_list_malloc = NULL;
    new_list_malloc = get_memory(sizeof(t_allocated) * new_list_malloc_size);
    ft_copy((char*)new_list_malloc, (char*)zone->list_malloc, zone->list_malloc_size * (sizeof(t_allocated)));
    munmap(zone->list_malloc, sizeof(t_allocated) * zone->list_malloc_size);
    zone->list_malloc_size = new_list_malloc_size;
    zone->list_malloc = new_list_malloc;
    return new_list_malloc;
}

/*
** Create a new allocated zone
** In which we can store malloc
*/
t_mem_zone *new_mem_zone(size_t size, t_mem_zone *before) {
    // ft_printf("%zu ", size);
    ft_putendl("entree");
    // TODO: Un seul call suffit ici, deux allocations pour rien
    t_mem_zone *zone = get_memory(sizeof(t_mem_zone));
    zone->mem_zone = get_memory(size);
    // On ne peut plus l'enlever
    zone->list_malloc = get_memory(sizeof(t_allocated) * 256);
    // TODO: set MEMORY TO 0
    zone->list_malloc_size = 256;
    zone->memory_size = size;
    zone-> memory_used = 0;
    zone->next = NULL;
    zone->before = before;
    return zone;
}

size_t  malloc_position(t_mem_zone *place, size_t asked_memory_size, size_t *i) {
    size_t position;

    *i= 0;
    position = 0;
    while ((*i) < place->list_malloc_size && place->list_malloc[*i].size) {
        ft_putendl("CA PLANTE1");
        
        if (place->list_malloc[*i].position == NULL && place->list_malloc[*i].size >= asked_memory_size) {
        ft_putendl("CA PLANTE2");
            
            return position;
        }
        position += place->list_malloc[*i].size;  
        (*i)++;
    }
    ft_putendl("ONSORT");
    // In case there is engouth place, but memory is fragmented
    if ((place->memory_size - position) < asked_memory_size) {
        ft_putendl("CA PLANTE");
 //       position = defragmentation(place);
    }
    return position;
}

void *add_malloc(t_mem_zone *place, size_t asked_memory_size) {
    size_t i;
    t_allocated new_malloc;
    size_t position;

    position = malloc_position(place, asked_memory_size, &i);

    ft_printf("used: %zu total %zu asked %zu\n", place->memory_used, place->memory_size, asked_memory_size);
    new_malloc.size = asked_memory_size;
    new_malloc.position = place->mem_zone + position;
    ft_printf("pos %p et I: %zu\n", new_malloc.position, i);
    // ft_printf("malloc deja fait %zu: Taille list malloc %zu\n", i,place->list_malloc_size);
    // Case there is more malloc done than the max number of malloc
    if (i == place->list_malloc_size) {
        ft_printf("NEEED BIGGER LIST MALLOC\n");
        ft_printf("%p\n", place->list_malloc);
        set_bigger_list_malloc(place);
        ft_printf("%p\n", place->list_malloc);
    }
    place->list_malloc[i] = new_malloc;
    place->memory_used += asked_memory_size;
    ft_printf("memzone: %p et position: %zu\n", place->mem_zone, position);
    ft_printf("adding: %p\n", place->mem_zone + position);
    return place->mem_zone + position;
}