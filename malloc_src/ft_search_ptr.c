#include "malloc.h"


void free_ptr(void *ptr, size_t size) {
    munmap(ptr, size);
}

void delete_mem_zone(t_mem_zone *zone, t_mem_zone **first_zone) {
    if (zone->before) {
        zone->before->next = zone->next;
        if (zone->next) {
            zone->next->before = zone->before;
        }
        free_ptr(zone->mem_zone, zone->memory_size);    
    free_ptr((void*)zone->list_malloc, sizeof(t_allocated) * 256);    
    free_ptr(zone, sizeof(t_mem_zone));    
    }
    else {
        // *first_zone = (*first_zone)->next;
        // if (*first_zone) {
        //     (*first_zone)->before = NULL;
        // }
    }
    

}

void clean_zone(t_mem_zone *zone, size_t pos, t_mem_zone **first_zone) {
    ft_putendl("coucou3");
    
    zone->memory_used -= zone->list_malloc[pos].size;
    zone->list_malloc[pos].size = 0;
    zone->list_malloc[pos].position = NULL;
    if (zone->memory_used == 0) {
        delete_mem_zone(zone, first_zone);
    }
    ft_putendl("coucou4");
    
}

int search_in_malloc(void *ptr, t_mem_zone *zone, t_mem_zone **first_zone) {
    size_t i;

    i = 0;
    while (i < zone->list_malloc_size) {
    ft_putendl("coucou2");
        
        if (zone->list_malloc[i].position == ptr) {
            clean_zone(zone, i, first_zone);
            return 1;
        }
        i++;
    }
    return 0;
}

int ft_search_ptr(void *ptr, t_mem_zone **first_zone) {
    int result;
    t_mem_zone *tmp = *first_zone;

    result = 0;
    ft_putendl("coucou1");
    while (tmp && result == 0) {
        result = search_in_malloc(ptr, tmp, first_zone);
        if (!result)
            tmp = tmp->next;        
    }
    return result;
}