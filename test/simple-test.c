#include "../libft/libft/libft.h"
// #include "../malloc_src/malloc.h"

int test_free(void *ptr) {
    free(ptr);
}

int test_malloc_size(size_t number, int print) {
    int *simple_malloc = (int*)ft_malloc(number * 4);
    if (print) {
        ft_printf("Pointeur retourné %p", simple_malloc);
    }
    if (!simple_malloc) {
        return 0;
    }
    int i = 0;
    while (i < number) {
        simple_malloc[i] = i;
        i++;
    }
    return 1;
}

int test_bad_value() {
    ft_putendl("Test with -1:");
    if (test_malloc_size(-1, 1) != 0) {
        ft_putendl("Failed");
    }
    ft_putendl("trying to allocate more than all memory");
    if (test_malloc_size(600000000000000000, 1) != 0) {
        ft_putendl("Failed");
    }
    return 0;
}

int main(int argc, char ** argv) {
    int i;
    ft_putendl("Simple test:");
    // Test simple
    ft_putendl("test 10 int");
    if (!test_malloc_size(10, 1)) {
        ft_putendl("Un malloc simple ne marche pas.");
    }
    ft_putendl("test 100000 int");
    if (!test_malloc_size(100000, 1)) {
        ft_putendl("Un malloc simple ne marche pas.");
    }
    ft_putendl("test 2000 multiple little malloc int");
    i = 0;

    while (i < 2000) {
        if (!test_malloc_size(10, 0)) {
            ft_putendl("Un malloc simple ne marche pas.");
            ft_printf("Erreur aprés %d recursions", i);
        }
        i++;
    }
    test_bad_value();
    return 0;
}