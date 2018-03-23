#include "malloc.h"

void  *search_allocated_zone(t_mem_zone *zone, size_t asked_memory_size) {
    int i;
    int position;

    i = 0;
    while (zone) {
        if (zone->memory_size - zone->memory_used >= asked_memory_size) {
            position = malloc_position(zone, asked_memory_size, &i);
            if (position != -1) {
                return add_malloc(zone, asked_memory_size, position, i);
            }
        }
        zone = zone->next;
    }
    return NULL;
}

/*
** search in all allocated zone if we can stock a new memory
** else create a new allocated zone
*/
t_mem_zone *get_memory_place(t_mem_zone *zone, size_t asked_memory_size, size_t zone_size) {
    void *place = search_allocated_zone(zone, asked_memory_size);
    if (!place) {
        // Get the last elem to add a next
        while (zone->next) {
            zone = zone->next;
        }
        place = new_mem_zone(zone_size, zone);
        zone->next = place;
        search_allocated_zone(place, asked_memory_size);
    }
    // ft_printf("MEM_ZONE %p\n", place->mem_zone);    
    return place;
    
}