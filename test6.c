#include <stdlib.h>
#include <unistd.h>

int	main()
{
	char *plop;

while (1){
	plop = malloc(1024);
	free(plop);
	write(1, "a", 1);
	plop=malloc(400);
	write(1, "b", 1);
	free(plop);
	plop=malloc(156);
	plop=malloc(156);
	plop=malloc(156);
	write(1, "c", 1);
	plop=malloc(400);
	write(1, "c", 1);
	write(1, "\n", 1);
}	// show_alloc_mem();
	return (0);
}
