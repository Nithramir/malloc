void test_no_error_realloc(size_t value)
{
	char *malloced = ft_malloc(20);
	ft_strcpy(malloced, "Yo\0");
	malloced = ft_realloc(malloced, value);

}
void test_no_error(size_t size)
{
	size_t i = 0;
	char *malloced = ft_malloc(size);
	while (i < size)
	{
		malloced[i] = 'd';
		
		i++;
	}
}

void test_no_error_free(size_t size)
{
	size_t i = 0;
	char *malloced = ft_malloc(size);
	// ft_putendl("FREE");
	ft_printf("pointeur: %p\n", malloced);
	while (i < size)
	{
		if (malloced[i] == 'd')
		{
			ft_putendl("Etrange");
			// exit(0);
		}
		malloced[i] = 'd';
		//// ft_printf("value: %d\n", i);
		
		i++;
	}
	// ft_putendl("sortie");
	// show_alloc_mem();
	// ft_free(malloced);
//	// // ft_printf("NoProblemWith: %zu\n", size);
}

void test_defragmentation()
{
	void *a = ft_malloc(1024);
	void *b = ft_malloc(1024);
	ft_free(b);
	void *c = ft_malloc(1024);
	void *d = ft_malloc(1024);
	void *e = ft_malloc(1024);
	
	show_alloc_mem();

}

int main(int argc, char **argv)
{
// test_defragmentation();
	// size_t size = getpagesize() * 200;
	test_no_error_realloc(10);
		show_alloc_mem();

	test_no_error_realloc(10);
	test_no_error_realloc(10);
	test_no_error_realloc(10);
	
	test_no_error(10);
	int i = 0;
	while (i < ft_atoi(argv[1]))
	{
		test_no_error_realloc(10);
		test_no_error_realloc(800);
		test_no_error_realloc(21);
		// show_alloc_mem();
	
		test_no_error_realloc(9000);

		test_no_error(60000);
		test_no_error_free(60000);
		test_no_error_free(1024);
		test_no_error_free(24);
		test_no_error_free(1);
		test_no_error_free(1023);
		test_no_error_free(getpagesize() * 65);
		// ft_printf("%zu\n", getpagesize() * 65);

		test_no_error(getpagesize() * 65);
		test_no_error(1024);
		test_no_error(3);
		test_no_error(4);
		test_no_error(5);
		test_no_error(6);
		ft_printf("value: %d\n", i);
		// show_alloc_mem();
		i++;
	}
	
	return 0;
}