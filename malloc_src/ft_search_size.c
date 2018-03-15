#include "malloc.h"

size_t search_size_in_malloc(void *ptr, t_mem_zone *zone) {
    size_t i;

    i = 0;
    while (i < zone->list_malloc_size) {
        if (zone->list_malloc[i].position == ptr) {
            // ft_printf("size  %zu", zone->list_malloc[i].size);
            return zone->list_malloc[i].size;
        }
        i++;
    }
    return 0;
}

size_t ft_search_size(void *ptr, t_mem_zone *first_zone) {
    size_t result;
    
    result = 0;
    while (first_zone && result == 0) {
        result = search_size_in_malloc(ptr, first_zone);
        if (!result)
            first_zone = first_zone->next;        
    }
    return result;
}