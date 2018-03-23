#include "malloc.h"

void set_struct_to_null(t_allocated *m) {
    m->size = 0;
    m->position = NULL;
}

int next_malloc_struct(t_mem_zone *zone, int j) {
    while (j < zone->list_malloc_size) {
        if (zone->list_malloc[j].size) {
            return j;
        }
        j++;
    }
}

void mov_malloc_struct(t_mem_zone *zone) {
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < zone->list_malloc_size) {
        if (!zone->list_malloc[i].size) {
            j = next_malloc_struct(zone, i);
            zone->list_malloc[i] = zone->list_malloc[j];
            set_struct_to_null(&zone->list_malloc[j]);
        }
        i++;
    }
}

void defragmentation(t_mem_zone *zone) {

}