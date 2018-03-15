#include "malloc.h"

t_mem_zone  *search_allocated_zone(t_mem_zone *zone, size_t asked_memory_size) {
    while (zone) {
       // ft_printf("memory_size: %zu, memory_used: %zu, askedmemrory: %zu\n", zone->memory_size, zone->memory_used, asked_memory_size);
        if (zone->memory_size - zone->memory_used >= asked_memory_size) {
            return (zone);
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
    t_mem_zone *place = search_allocated_zone(zone, asked_memory_size);
    if (!place) {
        // Get the last elem to add a next
        while (zone->next) {
            zone = zone->next;
        }
        place = new_mem_zone(zone_size, zone);
        zone->next = place;
    }
    // ft_printf("New allocated place: %p\n", place);
    return place;
    
}