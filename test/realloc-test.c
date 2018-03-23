#include "../malloc-src/malloc.h"

void test_no_error_realloc(size_t value) {
    char *malloced = ft_malloc(20);
    ft_strcpy(malloced, "Yo\0");
    malloced = ft_realloc(malloced, value);
    // // ft_printf("ptr %p\n", malloced);
    // ft_putendl(malloced);
}

void test_no_error(size_t size) {
    size_t i = 0;
    char *malloced = ft_malloc(size);
    // // ft_printf("pointeur: %p\n", malloced);
    while (i < size) {
        malloced[i] = 'd';
        // // ft_printf("value: %d\n", i);
        
        i++;
    }
//    ft_free(malloced);
//    // // ft_printf("NoProblemWith: %zu\n", size);
}

void test_no_error_free(size_t size) {
    size_t i = 0;
    char *malloced = ft_malloc(size);
    // ft_putendl("FREE");
    // // ft_printf("pointeur: %p\n", malloced);
    while (i < size) {
        if (malloced[i] == 'd') {
            // // ft_putendl("Etrange");
        }
        malloced[i] = 'd';
        //// ft_printf("value: %d\n", i);
        
        i++;
    }
    // ft_putendl("sortie");
    // show_alloc_mem();
    ft_free(malloced);
//    // // ft_printf("NoProblemWith: %zu\n", size);
}

int main(int argc, char **argv) {
    // size_t size = getpagesize() * 200;
    // test_no_error(size);
    // test_no_error(10);
    int i = 0;
    while (i < ft_atoi(argv[1])) {
        test_no_error_realloc(10);
       test_no_error_realloc(800);
        test_no_error_realloc(21);
        test_no_error_realloc(9000);
        
        // test_no_error(60000);
        // test_no_error_free(60000);
    
        // test_no_error_free(1024);
        // test_no_error_free(24);
        // test_no_error_free(1);
        // test_no_error_free(1023);
        // test_no_error_free(getpagesize() * 65);
        // // ft_printf("%zu\n", getpagesize() * 65);

        // test_no_error(getpagesize() * 65);
        test_no_error(1024);
        // test_no_error(3);
        test_no_error(4);
        test_no_error(5);
        test_no_error(6);
        ft_printf("value: %d\n", i);
        i++;
    }
    show_alloc_mem();
    
    return 0;
}
