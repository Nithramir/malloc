#include "malloc.h"
   // char *ptr = malloc(NULL, 7500, PROT_READ | PROT_WRITE, MAP_ANON |MAP_PRIVATE, -1, 0);

static t_malloc g_malloc = {0};

void *init_malloc(size_t size) {
    return new_mem_zone(size, NULL);
}

void *get_tiny_memory(size_t asked_memory_size, t_mem_zone **zone, size_t zone_size) {
    if (!(*zone)) {
        *zone = init_malloc(zone_size * 1);
        ft_printf("malloc initied %p\n", *zone);
    }
    t_mem_zone *place = get_memory_place(*zone, asked_memory_size, zone_size * 100);
    ft_printf("add malloc %p\n", place);
    return add_malloc(place, asked_memory_size);
}

void *get_large_memory(size_t asked_memory_size, t_mem_zone **zone, size_t zone_size) {
    ft_putendl("yolo");
    if (!(*zone)) {
        ft_putendl("yolo");
        *zone = init_malloc(zone_size);
        
        ft_printf("malloc initied %p\n", *zone);
    }
    t_mem_zone *place = get_memory_place(*zone, asked_memory_size, zone_size);
    // ft_printf("add malloc %p\n", place);
    return add_malloc(place, asked_memory_size);
}

void *ft_malloc(size_t asked_memory_size) {
    if (asked_memory_size < MALLOC_TINY) {
        return get_tiny_memory(asked_memory_size, &g_malloc.tiny, MALLOC_TINY);
    }
    else if (asked_memory_size < MALLOC_SMALL) {
        return get_tiny_memory(asked_memory_size, &g_malloc.small, MALLOC_SMALL);
    }
    else {
        return get_large_memory(asked_memory_size, &g_malloc.large, asked_memory_size + 1);
    }
    return NULL;
}

void ft_free(void *ptr) {
    int result;

    result = 0;
    if (g_malloc.large)
        result = ft_search_ptr(ptr, &g_malloc.large);
    if (!result && g_malloc.small)
        result = ft_search_ptr(ptr, &g_malloc.small);
    // ft_printf("1/ result: %d, g_malloc.tiny: %p\n", result, ptr);
    if (!result && g_malloc.tiny) {
        result = ft_search_ptr(ptr, &g_malloc.tiny);
    }
    // ft_printf("2/ result: %d, g_malloc.tiny: %p", result, g_malloc.tiny);   
}

void *ft_realloc(void *ptr, size_t new_size) {
    char *new_ptr;
    size_t size;

    size = 0;
    if (g_malloc.large)
        size = ft_search_size(ptr, g_malloc.large);
    if (!size && g_malloc.small)
        size = ft_search_size(ptr, g_malloc.small);
    // ft_printf("1/ size: %d, g_malloc.tiny: %p", size, ptr);
    if (!size && g_malloc.tiny) {
        size = ft_search_size(ptr, g_malloc.tiny);
    }
    // ft_printf("1/ size: %d, g_malloc.tiny: %p", size, ptr);
    
    // ft_printf("%zu\n", size);
    if (!size) {
        return (NULL);
    }
    ft_putendl("ici");
    
    new_ptr = (char*)ft_malloc(new_size);
    // ft_printf("%p\n", new_ptr);
    ft_putendl("ici");
    ft_strncpy(new_ptr, ptr, size);
    ft_free(ptr);
    return new_ptr;
}

void show_zone(t_mem_zone *first) {
    int i;
    t_allocated elem;
    int index = 0;

    while (first) {
        i = 0;
        while (i < first->list_malloc_size) {
            elem = first->list_malloc[i];
            if (elem.size != 0){
                ft_printf("%p - %p : %zu\n", elem.position, elem.position + elem.size, elem.size);
                index++;
            }
            i++;
        }
        // ft_putendl("");
        first = first->next;
    }
    ft_printf("Number of allocations: %d\n\n", index);
}

void show_alloc_mem() {
    ft_putendl("TINY");
    show_zone(g_malloc.tiny);
    ft_putendl("SMALL");
    show_zone(g_malloc.small);    
    ft_putendl("LARGE");
    show_zone(g_malloc.large);

}

void test_no_error_realloc(size_t value) {
    char *malloced = ft_malloc(20);
    ft_putendl("plw");
    ft_strcpy(malloced, "Yo\0");
    malloced = ft_realloc(malloced, value);
    // ft_printf("ptr %p\n", malloced);
    ft_putendl(malloced);
}

void test_no_error(size_t size) {
    size_t i = 0;
    char *malloced = ft_malloc(size);
    // ft_printf("pointeur: %p\n", malloced);
    while (i < size) {
        malloced[i] = 'd';
        // ft_printf("value: %d\n", i);
        
        i++;
    }
//    ft_free(malloced);
//    // ft_printf("NoProblemWith: %zu\n", size);
}

void test_no_error_free(size_t size) {
    size_t i = 0;
    char *malloced = ft_malloc(size);
    ft_putendl("FREE");
    // ft_printf("pointeur: %p\n", malloced);
    while (i < size) {
        if (malloced[i] == 'd') {
            // ft_putendl("Etrange");
        }
        malloced[i] = 'd';
        //ft_printf("value: %d\n", i);
        
        i++;
    }
    ft_putendl("sortie");
    // show_alloc_mem();
    ft_free(malloced);
//    // ft_printf("NoProblemWith: %zu\n", size);
}

int main(int argc, char **argv) {
    // size_t size = getpagesize() * 200;
    // test_no_error(size);
    // test_no_error(10);
    int i = 0;
    while (i < ft_atoi(argv[1])) {
       test_no_error_realloc(800);
        test_no_error_realloc(10);
        test_no_error_realloc(4);
        
        test_no_error_realloc(9000);
  //
        test_no_error(60000);
        test_no_error_free(60000);
    
        test_no_error_free(1024);
        test_no_error_free(24);
        test_no_error_free(1);
        test_no_error_free(1023);
        test_no_error(1024);
        ft_printf("%zu\n", getpagesize() * 65);
        test_no_error(getpagesize() * 65);
        test_no_error_free(getpagesize() * 65);

        test_no_error(3);
        test_no_error(4);
        test_no_error(5);
        test_no_error(6);
        ft_printf("value: %d\n", i);
        i++;
    }
    show_alloc_mem();
    
    return 0;
}