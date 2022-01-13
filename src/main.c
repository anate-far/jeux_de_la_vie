#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "grid.h"

int main(void)
{
	tools_memory_init();

	grid* tab = grid_create(9, 9);

	grid_set(tab, 3 , 3, 1);
	grid_set(tab, 4 , 3, 1);
	grid_set(tab, 5 , 3, 1);
	grid_set(tab, 3 , 2, 1);

	grid_debug(tab);
	printf("\n\n");

	grid_check(tab);

	grid_debug(tab);

	grid_destroy(tab);

	tools_check_at_end_of_app();

	return EXIT_SUCCESS;
}
